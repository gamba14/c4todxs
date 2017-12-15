/**Mi bonito shell- Agustin Gambirassi
 * fuente: Guia C de la cursada e investigacion personal **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>


#define CMD			2
#define CD			3
#define SALIR			99
#define ERROR			-1
#define NO_INTERACTIVO	        0
#define INTERACTIVO		1
#define PROMPT                  "[MyShellE]=>"
#define SEGUNDO_PLANO           "&"
#define ENTRADA                 "<"
#define SALIDA                  ">"

void prompt();
void inicio();
void ingreso();
void ingresoLinea();
void parseoLinea();
void proceso();
void ejecutoProceso();
void libero();


struct {
	pid_t pid;		 		// id de proceso del shell
	pid_t pgid;				// id del grupo de proceso del shell
	int interactivo; 			// ¿comando en foreground?
	int input; 				// descriptor de archivo de stdin del shell
	char *comando;	 		// comando ingresado por el usuario
	char *error; 			// error (de parsing,etc.) del ultimo comando ingresado
	char *arg[64]; 			// cada elemento es una parte significativa del comando
						// ingresado por el usuario
	int narg; 			// cantidad de partes significativas que tiene el
						// comando actual (no puede superar de 64)
	int op; 			// luego del parsing, se determino este tipo de comando
	int salir; 				// ¿salgo del shell?
	char *entrada; 			// nombre de archivo al cual redirigir entrada
	char *salida; 			// nombre de archivo al cual redirigir salida
} sh;


void inicio() {

	sh.pid=getpid();
	sh.pgid=getpgrp();
	sh.entrada=NULL;
	sh.salida=NULL;
	sh.error=NULL;
	sh.salir=0;
	sh.input=STDIN_FILENO;
	
}


// shell - rutina de ingreso de comando por teclado
void ingreso() {
	prompt(); 				// simbolo a mostrar por pantalla
	ingresoLinea(); 			// ingreso de una linea de texto por teclado
	parseoLinea(); 			// separacion de la linea ingresada en "tokens"
}


// muestro prompt 
void prompt() {
   printf("\n");
   printf(PROMPT);
}


void ingresoLinea() {
	int i=0;
	int nbuf=0;				  //cantidad de caracteres almacenados en buf
	int nbufsize=0;			 //este es el tamaño que se agregara, al pedir mas memoeria con realloc
	char c;
	int nbytes= sizeof(char);
	char *buf = (char *) malloc(nbytes); //buffer donde se almacenan los caracteres leídos

	if (buf!=NULL) {

		for(i=0;buf[i-1]!='\n';i++) {
			c = (char) getc(stdin);	//lee un caracter por teclado (stdin asociado a dispositivodel teclado)
			buf[i]=c;
			nbuf=strlen(buf);
			if((nbuf % nbytes)==0) {
				nbufsize+=nbytes;
				buf = (char *) realloc(buf,nbufsize);//cuando se llene el buffer, vuelve a pedir mas memoria
			}
		}
		buf[nbufsize-1]='\0';
		sh.comando=buf;
	}
}


void parseoLinea() {

    int i=0;
	char *buffer = (char *) malloc(strlen(sh.comando)+1);			
	sh.error = (char *) malloc(256);
	strcpy(buffer,sh.comando); 			
	buffer = strtok(sh.comando, " ");	
	while (i < 64 && buffer != NULL) { 	      
		sh.arg[i] = buffer; 		     
		buffer = strtok(NULL, " ");	    
		i++; 				  
	} 						
	sh.narg=i;			

	if(i == 64 && buffer != NULL) {
		strcpy(sh.error,"Error de parsing");
		sh.op=ERROR;
	}

	if (sh.op!=ERROR)sh.op=CMD;

 	if(strcmp(sh.arg[0],"cd")==0) sh.op=CD;
 	
	if( strcmp(sh.arg[0],"exit")==0 ) {sh.op=SALIR; sh.salir=1;}

	if( strcmp(sh.arg[sh.narg-1],SEGUNDO_PLANO)==0 ) { 
		sh.interactivo = NO_INTERACTIVO;
		
	}
	else sh.interactivo = INTERACTIVO;

	for (i=0; i < sh.narg-1; i++)
		if(strcmp(sh.arg[i],ENTRADA)==0) {
			sh.entrada=sh.arg[i+1];
			
		}
	for (i=0; i < sh.narg-1; i++)
		if(strcmp(sh.arg[i],SALIDA)==0){
			sh.salida=sh.arg[i+1];
			
		}
	
	free(buffer); 
}

//Handler para SIGCHLD
void hijoHandler(int sig) {			
			while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
			
			
}

		

void proceso() {

	
	switch(sh.op) {
		case SALIR:		     				 						       
			sh.salir=1; 								
			break;

		case CD:                    		                  	     		       	   
    		if(sh.narg==1) {       
     				char *dir = getcwd(NULL,0);
    	    			if (dir != NULL) printf("%s\n",dir);
            			else fprintf(stdout,"ejecutoProceso(): No se pudo obtener el directorio actual\n");
   			}
    			else                                                  					
      				if (chdir(sh.arg[1]) == -1) fprintf(stdout,"ejecutoProceso(): Directorio INVALIDO\n"); 
			break;
			
		case CMD:
			signal(SIGCHLD,hijoHandler);
{			pid_t pid = fork();
			//printf(pid);
			switch (pid) {
				case -1:									
					printf("Error en fork()!\n");
					break;
				case 0: {									
					setpgrp(); 					
					pid_t chpid = getpid();	
					pid_t fgpid = getpgrp();							
					
					if (sh.interactivo)	
						{
							ejecutoProceso();
							signal(SIGTTOU,SIG_IGN);//ignoro la señal q suspende el proceso
							tcsetpgrp(fgpid,chpid);//creo que debo llamarlo desde proceso padre, no desde hijo
													
						} 				      
					else {											
							printf("Proceso [%d] ejecutando en background\n", (int) chpid);
							ejecutoProceso();
							signal(SIGTTOU,SIG_IGN);//de nuevo, maldito zsh ¬¬
							tcsetpgrp(chpid,sh.pgid);
							/** nota respecto a esta seccion, resulta que ejecuta en bg,
							 * por ejemplo: le paso el comando arduino & y se ejecuta, luego no 
							 * vuelve a mostrar el prompt, y si cierro la ventana no me informa que
							 * el proceso termino**/
							 	
						}				
					break;
				}
				default: 
					setpgid(pid, pid);
					if (sh.interactivo) {
						signal(SIGTTOU,SIG_IGN);//de nuevo trato de ignorar.
						tcsetpgrp(sh.input,pid); 							
						int terminationStatus;							
						while(waitpid(pid, &terminationStatus,WUNTRACED | WNOHANG) == 0);
						tcsetpgrp(sh.input, sh.pgid); 						
					}
					break;
			}
			break;
		}
	}

}


void ejecutoProceso() {    
    
    int ret = execvp(sh.comando,sh.arg);
    if (ret == -1) {
		strcpy(sh.error,"ejecutoProceso(): Comando no encontrado");
		printf("No existe comando\n");
		sh.op=ERROR;
		}
    
   
}



void libero(){

	int i=0;
	while(i<sh.narg){
		sh.arg[i]=NULL;
		i++;
	}
	//free (sh.comando);
	sh.comando=NULL;
	sh.entrada=NULL;
	sh.salida=NULL;
	free(sh.error);
	sh.error=NULL;
}

int main(void) {
	inicio();				
	ingreso(); 				
	while(!sh.salir) {		
		proceso(); 			
		libero(); 			
		ingreso(); 			
	} 					
return 0;
}



/* 
   MiniShell que ejecuta comandos con y sin argumentos en background y
   en foreground
*/

//----------------------------cabeceras
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//---------------------------Prototipos
void ponerAlarma(void);
void quitarAlarma(void);

void elmatazombies(void);
void ingresarComando(char *) ;
void parserComando(char *, char  * [64]) ;
void liberarMemoria(char * v[]) ;

int EnBackground ;

//---------------------------Funcion principal del programa
int main(void)
{
  pid_t pid;
  char * comando = (char *) malloc(64) ; 
  char * comandopartido [64] ;
  ingresarComando(comando) ; 
  parserComando(comando,comandopartido);
  while(strcmp(comandopartido[0],"exit"))
    { 
      pid = fork();
      if(pid == 0)
            {
              execvp(comandopartido[0],comandopartido);
              printf("Comando invalido\n");          
              exit(-1);
            }
      else
         if(pid > 0)
               {
                 if (EnBackground == 0)
                    {
                       quitarAlarma();                      
                       waitpid(pid,0,0);
                       ponerAlarma();
                    }
                 else
                    {
                      // ponerAlarma();
                    }  
                 usleep(50000);
                 ingresarComando(comando) ;
                 liberarMemoria(comandopartido) ;
                 parserComando(comando,comandopartido);
               }
         else
            perror("ERROR FORK\n");
    } 
}                

//------Definicion de la funcion para asignar a la recepcion de la señal
//      SIGALRM la ejecucion de la funcion elmatazombies cada 30 segundos
void ponerAlarma(void) 
{
   signal(SIGALRM,(void*) elmatazombies) ;
   raise(SIGALRM);   
   alarm(30);
}

void quitarAlarma(void) 
{
   //raise(SIGALRM);
   signal(SIGALRM,SIG_DFL) ;
}


//------Definicion de la funcion para recuperar los estados de los procesos hijos que hicieron exit
void elmatazombies(void)
{
  printf("***************** el mata zombies en accion *******************\n");
  while(waitpid(-1,0,WNOHANG)!=-1);
  alarm(30);
}              

//------Definicion de la funcion para ingresar el comando con argumentos
void ingresarComando(char * comando)
{
  memset(comando,'\0',64);
  printf("MI PROMPT "); 
  gets(comando);
}

//------Definicion de la funcion para separar el comando de los argumentos 
void parserComando(char * comando , char  * comandopartido [64] )
{
  int i = 0 ; int j = 0 ; int z = 0 ; 
  EnBackground = 0 ; 
  do 
  {
    comandopartido[z] = (char *) malloc(64); 
    for(j=0 ; comando[j+i] != '\0' && comando[j+i] != ' ' && comando[j+i] != '&' ; j++)
                comandopartido[z][j] = comando[j+i] ;
        comandopartido[z][j] = 0 ;
            
//printf("----------------- %d **%s**\n",z,comandopartido[z]) ;
     j++ ; z++ ; i += j ;
  } while( comando[i] != '\0' && comando[i] != '&');
   if (comando[i] == '&')
        EnBackground = 1 ;   
  comandopartido[z] = (char *) malloc(2); 
  comandopartido[z] =  0 ;
//printf("----------------- %d **%s**\n",z,comandopartido[z]) ; 
}

//------Definicion de la funcion para liberar la memoria dinamica que fue asignada con malloc
//      para comandopartido
void liberarMemoria(char * v[]) 
{
   int z ;
   for( z=0 ; v[z] != NULL ; z++)  free (v[z]);
}
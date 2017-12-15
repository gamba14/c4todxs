/* este es el ejemplo del productor consumidor
 * implementado en C del capitulo 6 del libro de 
 * silberchatz
 */
 
 #include "operipc.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/shm.h>
 #include <sys/ipc.h>
 #define BUFF_SIZE 5 
 char productor(void);
 
 int main(int argc,char **argv){
	 system("sh kill_ipcs.sh");
	 system("./init_prodcons");
	 //creo las areas de memoria compartida
	 //para el buffer y para el contador.
	 int buffershm = shmget(0xa,0,0);
	 int contadorshm = shmget(0xb,0,0);
	 int semid = semget(0xa,0,0);
	 
	 int *contador,pone =0;
	 contador = (int *) shmat(contadorshm,0,0);
	 char * buffer;
	 buffer = (char *) shmat(buffershm,0,0);
	 
	 while(1){
		 while(*contador != BUFF_SIZE){
			 P(semid,0);
			 buffer[pone] = productor();
			 (*contador)++;
			 printf("Productor: ""\x1b[32m""Produjo %c\n""\x1b[0m",buffer[pone]);
			 pone = (pone +1)%BUFF_SIZE;
			 V(semid,0);
		 }		 
	 }
	 
} 

char productor(void){
	static int letra = 'a'-1;
	if(letra == 'z'){
		letra = 'a';
		}
	else{
		letra ++;
		return letra;
		
	}
}

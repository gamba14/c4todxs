/*
 * Este proceso crea una cadena de n procesos indicados por linea de comandos
 *	a medida que terminan los procesos hijos se le va informando su finalizacion
 * la variante de este codigo puede ser la implementacion de waitpid(-1,status,WNOHANG)
 * pero resulta mas lindo y mas facil de acordarse usar wait(&status)
 */
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	printf("Soy el inicio de la cadena con PID %d\n",getpid());
	pid_t pid;
	int n = atoi(argv[1]),i,status,retval;
	for (i=0;i<n;i++){
		pid = fork();
		if(pid == 0){
			printf("Soy el proceso %d, hijo del proceso %d\n",getpid(),getppid());
			sleep(1);
			}
		else break;
				
	}
	while((retval = wait(&status)) >-1){
		printf("Termino proceso %d con codigo %d\n",retval,(status/256));
	}	
}
		

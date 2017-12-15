/*
 * 
 * 
 * 
 * 
 * 
 * fork() creacion de N procesos hijos por linea de comandos
 * con sincronizacion basica entre procesos
*/
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int i;
	if ( argc == 2 ) {
		int n = atoi(argv[1]),estado; 
		pid_t pid,wpid;
		if ( n > 0 ) {
			printf("Proceso padre ID %d\n",getpid());
			// todo OK!
			for(i=0;i<n;i++) {
				// doy tantas vueltas como indique el usuario por linea de comando!
				pid = fork();
				if ( pid == 0 ) {
					// creacion de proceso hijo
					printf("Proceso hijo ID %d hijo de %d que devuelve %d\n",getpid(),getppid(),i);
					sleep(1);
					exit(i);
				}
			}
			// proceso padre queda bloqueado esperando por la finalizacion del proceso hijo
			printf("Proceso padre: espero por la finalizacion de hijos!\n");
			while( (wpid = wait(&estado)) != -1 ) {
				printf("Proceso padre: Finalizo proceso hijo %d y retorno %d\n",wpid,(estado/256));
			}
			printf("Proceso padre: fin de espera!\n");
		} else {
			printf("%d es un valor incorrecto, debe ser mayor que cero\n",n);
		}
	} else {
		printf("Error! forma de uso:\n./fork6 <cantidad de procesos hijos>\n");
	}
	printf("Proceso padre fin!\n");
	exit(0);
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

int main(int argc, char **argv) {
	int pipe1[2];  
	int pipe2[2];  
	pipe(pipe1);
	pipe(pipe2);
	if (fork()) {
		// padre P
		if (fork()) {
			// padre P
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			printf("\n  		 I seek you jaja\n");
			printf("\n  		******\n");
			while(wait(NULL) != -1);
			sleep(1);
			printf("\n\E[0;31m Fin del proceso Padre\n \n");
		} else {
			// hijo! H2
			if (fork()) {
				// hijo! H2
				close(pipe2[0]);
				close(pipe1[1]);
				close(pipe1[0]);
				char linea[255];
				while(strncmp(linea,"chau",4) != 0) {
					gets(linea);
					printf("			H2 >> %s",linea);
					write(pipe2[1],linea,strlen(linea));
				}
				close(pipe2[1]);
				printf("\n			H2 fin!\n");
			} else {
				// nieto! N2
				close(pipe2[0]);
				close(pipe1[1]);
				close(pipe2[1]);
				char linea[255];
				int n;
				while(strncmp(linea,"chau",4) != 0) {
					sleep(1);
					n = read(pipe1[0],linea,255);
					linea[n]='\0';
					printf("\n			N2 << %s\n\n",linea);
				}
				close(pipe1[0]);
				printf("\n 			N2 fin!\n");
			}
		}
	} else {
		// hijo! H1
		if (fork()) {
			// hijo! H1
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe1[0]);
			char linea[255];
			while(strncmp(linea,"chau",4) != 0) {
				gets(linea);
				printf("\n H1 >> %s",linea);
				write(pipe1[1],linea,strlen(linea));
			}
			close(pipe1[1]);
			printf("\n H1 fin!\n");
		} else {
			// nieto! N1
			close(pipe1[0]);
			close(pipe2[1]);
			close(pipe1[1]);
			char linea1[255];
			int n;
			while(strncmp(linea1,"chau",4) != 0) {
				sleep(1);
				n = read(pipe2[0],linea1,255);
				linea1[n]='\0';
				printf("\n N1 << %s\n\n",linea1);
			}
			close(pipe2[0]);
			printf("\n N1 fin!\n");
		}
	}
	return 0;
}

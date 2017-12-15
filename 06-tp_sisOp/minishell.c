#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>

int main(void){
	printf("X->");
	char comando[64];
	memset(comando,'\0',64);
	scanf("%s",comando);
	while(strcmp(comando,"salir")){
		
		pid_t pid = fork();
		switch(pid){
			case 0:{
					execlp(comando,comando,NULL);
					printf("error: no se ha encontrado comando\n");
					exit(0);
					break;
					}
			case -1:{
					perror("Error de FORK");
					break;
				}
			default:{ 
				waitpid(pid,0,0);
				printf("X->");
				memset(comando,'\0',64);
				scanf("%s",comando);
			}
			
		}
	}
	exit(0);
}

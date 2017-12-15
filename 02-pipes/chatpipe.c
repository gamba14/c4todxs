#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	pid_t pid;
	int p[2];
	int p2[2];
	int status;
	pipe(p);
	pipe(p2);
	pid= fork();
	if(pid > 0){		
		//estoy en el proceso padre
		pid=fork();
		if(pid ==0){
			//estoy en el proceso hijo2
			pid=fork();
			if(pid > 0){
				//estoy en el hijo2
				//codigo del hijo 2
				char entrada[512];
				close(p2[0]);
				close(p[1]);
				close(p[0]);
				do{
					printf("hijo 2 envia: ");
					memset(entrada,0,512);
					gets(entrada);
					write(p[1],entrada,strlen(entrada)+1);
				}while(strcmp(entrada,"!exit"));
				close(p2[1]);
				wait(&status);				
			}
			else{
				//codigo del nieto 2
				char entrada[512];
				char byte;
				int lei,i;
				close(p[1]);
				close(p2[1]);
				close(p2[1]);
				do{
					printf("nieto 2 recibe: ");
					memset(entrada,0,512);
					i=0;
					while((lei = read(p[0],&byte,1)) && byte != '\0'){
						entrada[i++] = byte;
					}
					entrada[i] = '\0';
					printf("%s\n",entrada);
				}while(strcmp(entrada,"!exit"));
				close(p[1]);					
			}
		}
		else{
			//estoy en el padre
			close(p[0]);
			close(p[1]);
			close(p2[0]);
			close(p2[1]);
			wait(&status);
			wait(&status);
		}
		wait(&status);
	}
	else{
		//estoy en el proceso hijo 1
		pid = fork();
		if(pid >0){
			//estoy en el hijo 1
			//codigo del hijo 1
			char entrada[512];
			close(p[0]);
			close(p2[1]);
			close(p2[0]);
			do{
				printf("hijo 1 envio: ");
				memset(entrada,0,512);
				gets(entrada);
				write(p[1],entrada,strlen(entrada)+1);
			}while(strcmp(entrada,"!exit"));
			close(p[1]);
			wait(&status);
		}
		else{
			//estoy en el nieto 1
			//codigo del nieto 1
			char entrada[512];
			char byte;
			int lei,i;
			close(p2[1]);
			close(p[1]);
			close(p[0]);
			do{
				printf("recibo nieto 1: ");
				memset(entrada,0,512);
				i=0;
				while((lei = read(p2[0],&byte,1)) && byte != '\0'){
					entrada[i++] = byte;
				}
				entrada[i]='\0';
				printf("%s\n",entrada);
			}while(strcmp(entrada,"!exit"));
			close(p2[0]);
			}
		}
		return 0;
}

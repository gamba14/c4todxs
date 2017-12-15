#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc , char **argv){
	pid_t pid;
	int p[2],status,i;
	char buff;
	char entrada[512];
	pipe(p);
	pid = fork();
	if(pid == 0){
		while(1){
		//estoy en el proceso hijo
			close(p[1]);
			while(read(p[0],&buff,1) >1){
				entrada[i++] = buff;
			}
			if(strcmp(entrada,"PING")){
				printf("hijo responde PONG\n");
			}
			close(p[0]);
			sleep(1);
		}
				
		
	}
	else{
		while(1){
		close(p[0]);
		printf("padre manda PING\n");
		write(p[1],"PING",strlen("PING"));
		close(p[1]);
		sleep(1);		
	}
		wait(&status);
	}
}

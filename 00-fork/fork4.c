#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv){
	pid_t pid;
	int status,hijos,retval1;
	hijos = atoi(argv[1]);
	for(int i=0;i<hijos;i++){
		pid = fork();
		if(pid == 0){
			printf("soy el proceso %d\n",getpid());
			sleep(1);
			exit(i);
		}
		else{
			while((retval1 = waitpid(-1,&status,0))>-1){
				printf("Termino proceso %d con status %d\n",retval1,(status/256));
			}
		}
	}
}

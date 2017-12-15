#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
int i;
int main(int argc, char **argv){
	if(argc == 2){
		int n = atoi(argv[1]);	
		for(i=0;i<n;i++){
			pid_t pid = fork();		
			if(pid == 0){
				printf("Soy el proceso hijo de %d con PID %d %d\n",getppid(),getpid(),i);
				sleep(1);
				exit(i);
			}
		}
	}
exit(0);
}

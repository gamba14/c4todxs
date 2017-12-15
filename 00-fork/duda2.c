#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	pid_t pid;
	int i;
	int status = 0;
	for(i=0;i<3;i++){
		pid = fork();
		if(pid > 0) break;
	}
	int pidter = wait(&status);
	printf("Padre %d, hijo %d,terminado %d status %d\n",getppid(),pid,pidter,(status/256));
	exit(i);
}
	

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
main(){
	system("ps");
	printf("soy el padre %d\n",getpid());
	fork();
	fork();
	fork();
	wait(SIGCHLD);
	printf("soy el proceso %d,hijo del proceso %d\n",getpid(),getppid());
	exit(0);
	}

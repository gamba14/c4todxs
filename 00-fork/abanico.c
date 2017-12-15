#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	pid_t pid;
	int status,i,retval;
	printf("Soy el proceso padre %d\n",getpid());
	int n = atoi(argv[1]);
	for(i=0;i<n;i++){
		pid = fork();
		if(pid){
			//printf("Soy el proceso %d\n",getpid());
			sleep(1);
			//exit(2);			
		}
		else{
			 printf("Soy el proceso %d, hijo de %d\n",getpid(),getppid());
			 exit(i);
		 }
	}
	
	while((retval = wait(&status)) > -1){
		printf("Finalizo proceso %d con status %d\n",retval,(status/256));
	}
	printf("termina el padre\n");	
	return 0;
}

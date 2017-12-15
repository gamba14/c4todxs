#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>



void chldhandler(int sig){
	pid_t pid;
	pid = wait(NULL);
	printf("PID %d ha terminado\n",pid);
	
}	

void alrmhandler(int sig){
	printf("sono sono sono, me llaman del bar de moe \n");
	exit(0);
}		


int main(int argc, char **argv){
	int status;
	pid_t pid;
	signal(SIGCHLD,chldhandler);
	pid = fork(); //creo al primer hijo
	if(pid == 0){
		//estoy en el primer hijo
		signal(SIGALRM,alrmhandler);
		signal(SIGCHLD,chldhandler);
		printf("soy el proceso %d con PPID %d\n",getpid(),getppid());
		alarm(4);
		pid = fork();
		if(pid == 0){
			//estoy en el primer nieto
			printf("soy el proceso %d con PPID %d\n",getpid(),getppid());
			signal(SIGCHLD,chldhandler);
			pid = fork();
			if(pid == 0){
				//estoy en el bisnieto
				printf("soy el proceso %d con PPID %d\n",getpid(),getppid());
				sleep(1);
				exit(0);
			}
			sleep(1);
			exit(0);
			//estoy en el nieto y espero a que termine su hijo			
		}
		sleep(1);
		exit(0);		
	}
	while((pid = waitpid(-1,&status,0)) != -1){
		printf("obtuve %d del proceso hijo PID: %d\n",(status/256),pid);
	}	
	return 0;
}
				


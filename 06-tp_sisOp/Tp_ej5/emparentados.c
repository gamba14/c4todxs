#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char **argv){
	//establecer los semaforos
	sem_t * semA ;
    sem_t * semB ;
    sem_t * semC ;
    sem_t * semX ;
    
    sem_unlink("/semA");
    sem_unlink("/semB");
    sem_unlink("/semC");
    sem_unlink("/semX");

    semA = sem_open("/semA",O_CREAT|O_EXCL,0644,1) ;
    semB = sem_open("/semB",O_CREAT|O_EXCL,0644,1) ;
    semC = sem_open("/semC",O_CREAT|O_EXCL,0644,0) ;
    semX = sem_open("/semX",O_CREAT|O_EXCL,0644,0) ;
    
	for(int i=0;i<2;i++){
		pid_t pid = fork(); //creo el primer proceso hijo
	
		if(pid == 0){
			printf("Soy el proceso Hijo con PID %d\n",getpid());
		}		
	}
exit(0);	
	
}

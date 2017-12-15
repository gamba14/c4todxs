#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void){
		
	int shm01 = shmget(0XC,0,0);
	int * valin;
	valin = (int *) shmat(shm01,0,0);
	sem_t * semA;
	sem_t * semX;
	
	semA = sem_open("/semA",0);
	semX = sem_open("/semX",0);
	
	while(1){
		sem_wait(semA);
		(*valin)++;	
		sleep(1);		
		sem_post(semX);
	}
	
}

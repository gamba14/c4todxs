#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char **argv){
	
	int shm01 = shmget(0xc,0,0);
	int *valin;
	valin = (int*) shmat(shm01,0,0);
	
	sem_t *semA;
	sem_t *semB;
	sem_t *semC;
	sem_t *semX;
	
	semA = sem_open("/semA",0);
	semB = sem_open("/semB",0);
	semC = sem_open("/semC",0);
	semX = sem_open("/semX",0);
	
	while(1){
		sem_wait(semC);
		sem_wait(semX);
		printf("recibi del productor %d\n",*valin);
		sleep(1);
		//shmdt(valin);
		sem_post(semA);
		sem_post(semB);
	}
}
	


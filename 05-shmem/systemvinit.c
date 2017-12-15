#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	int semid = semget(0xa,2,IPC_CREAT|IPC_EXCL|0600);
	int shm01 = shmget(0xa,1,IPC_CREAT|IPC_EXCL|0600);
	
		
	printf("shmid %d\n",shm01);
	printf("semid %d\n",semid);
	
	semctl(semid,0,SETVAL,1);
	semctl(semid,1,SETVAL,0);
	
	exit(0);
	
}


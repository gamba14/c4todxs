#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

int main(int argc, char **argv){
	int shmid = shmget(0xa,sizeof(int),IPC_CREAT|IPC_EXCL|0777);
	int semid = semget(0xa,4,IPC_CREAT|IPC_EXCL|0777);
	
	printf("Semaforo: %d \nShm: %d\n",semid,shmid);
	
	semctl(semid,0,SETVAL,1);
	semctl(semid,1,SETVAL,1);
	semctl(semid,2,SETVAL,0);
	semctl(semid,3,SETVAL,0);
	
	exit(0);
}
	

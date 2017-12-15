#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "operipc.h"

int main(int argc, char **argv){
	int semid = semget(0xa,0,0);
	int shm01 = shmget(0xa,0,0);
	
	char *varchar;
	varchar = (char *) shmat(shm01,0,0);
	
	while(1){
		P(semid,1);
		printf("SC:B recibo %c\n",*varchar);
		sleep(1);
		V(semid,0);
	}
}

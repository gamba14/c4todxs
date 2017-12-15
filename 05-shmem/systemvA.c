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
	*varchar = 'a';		
	while(1){
		P(semid,0);
		printf("SC:A envio %c\n",*varchar);
		(*varchar)++;
		sleep(1);
		V(semid,1);
	}
}

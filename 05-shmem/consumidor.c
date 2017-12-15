#include "operipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define BUFF_SIZE 5 

int main(int argc, char **argv){
	
	int shmcontador = shmget(0xb,0,0);
	int shmletra =shmget(0xa,0,0);
	int sale =0;
	
	int *contador = (int *) shmat(shmcontador,0,0);
	char *letra = (char *) shmat(shmletra,0,0);
	int semid = semget(0xa,0,0);
	
	while(1){
		while(*contador != 0){
			P(semid,0);
			*contador = *contador -1;
			printf("Consumidor:""\x1b[32m""consume %c\n""\x1b[0m",letra[sale]);
			sale = (sale+1)%BUFF_SIZE;
			sleep(1);
			V(semid,0);
		}
	}
	shmdt(contador);
	shmdt(letra);
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "operipc.h"

int main(int argc, char **argv) {
	int saca=0;
	int semid = semget(0xA,0,0);
	int shmbuffer = shmget(0xA,0,0);
	int shmcontador = shmget(0xB,0,0);
	char *buffer = (char *) shmat(shmbuffer,0,0);
	int *dircontador = (int *) shmat(shmcontador,0,0);
	char letra;
	
	while(1) {
		while(*dircontador == 0);
		P(semid,0);
			// SC
			letra=buffer[saca];
			*dircontador = *dircontador - 1;
			printf("shm_consumidor:consumi %c de %d\n",letra,saca);
		V(semid,0);
		saca = (saca +1) % BUFSIZ;
	}
}


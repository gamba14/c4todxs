#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "operipc.h"
char produccion();

int main(int argc, char **argv) {
	int pone=0;
	int semid = semget(0xA,0,0);
	int shmbuffer = shmget(0xA,0,0);
	int shmcontador = shmget(0xB,0,0);
	char *buffer = (char *) shmat(shmbuffer,0,0);
	int *dircontador = (int *) shmat(shmcontador,0,0);
	
	while(1) {
		while(*dircontador == BUFSIZ);
		P(semid,0);
			// SC
			buffer[pone]=produccion();
			*dircontador = *dircontador +1;
			printf("shm_productor:produje %c en %d\n",buffer[pone],pone);
		V(semid,0);
		pone = (pone +1) % BUFSIZ;
	}
}

char produccion() {
	static char letra = 'A'-1;
	if ( letra == 'Z' ) letra = 'A';
	else letra++;
	return letra;
}

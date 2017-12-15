#include "operipc.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/shm.h>
 #include <sys/ipc.h>
 
 int main(int argc, char **argv){

		int buffershm = shmget(0xa,5,IPC_CREAT|IPC_EXCL|0777);
		int contadorshm = shmget(0xb,sizeof(int),IPC_CREAT|IPC_EXCL|0777);	 
		int *contador;
		int semid = semget(0xa,1,IPC_CREAT|IPC_EXCL|0666);
		semctl(semid,0,SETVAL,1);
		contador = shmat(contadorshm,0,0);
		*contador = 0;
		printf("TODO OK\n""\x1b[33m""Semaforo: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",semid);
		printf("\x1b[33m""Contador: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",contadorshm);
		printf("\x1b[33m""Buffer: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",buffershm);
		exit(0);
	}

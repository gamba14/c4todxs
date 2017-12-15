#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
	
	sem_t * semA;
	sem_t * semB;
	sem_t * semC;
	sem_t * semX;
	
	int ValsemA ;
	int ValsemB ;
	int ValsemC ;
	int ValsemX ;
	
	int intid = shmget(0XC,sizeof(int),IPC_CREAT|IPC_EXCL|0777);
	printf("%d\n",intid);
	
	sem_unlink("/semA");
	sem_unlink("/semB");
	sem_unlink("/semC");
	sem_unlink("/semX");

	semA = sem_open("/semA",O_CREAT|O_EXCL,0644,1);
	semB = sem_open("/semB",O_CREAT|O_EXCL,0644,1);
	semC = sem_open("/semC",O_CREAT|O_EXCL,0644,0);
	semX = sem_open("/semX",O_CREAT|O_EXCL,0644,0);
	
	sem_getvalue(semA,&ValsemA);
	sem_getvalue(semB,&ValsemB);
	sem_getvalue(semC,&ValsemC);
	sem_getvalue(semX,&ValsemX);

	printf("semA = %d \n",ValsemA);
	printf("semB = %d \n",ValsemB);
	printf("semC = %d \n",ValsemC);
	printf("semX = %d \n",ValsemX);
	
	//printf("semaforos:\n A=%d\nB=%d\nC=%d\nX=%d\n",semA,semB,semC,semX);
	
	exit(0);
}

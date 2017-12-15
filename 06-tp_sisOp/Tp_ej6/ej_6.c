#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

int main(void) {
	sem_t *semA;
	sem_t *semB;
	sem_t *semC;
	sem_t *semD;
	int ValsemA;
	int ValsemB;
	int ValsemC;
	int ValsemD;
	sem_unlink("semA");
	sem_unlink("semB");
	sem_unlink("semC");
	sem_unlink("semD");
	semA=sem_open("semA",O_CREAT|O_EXCL,0644,0);
	semB=sem_open("semB",O_CREAT|O_EXCL,0644,1);
	semC=sem_open("semC",O_CREAT|O_EXCL,0644,0);
	semD=sem_open("semD",O_CREAT|O_EXCL,0644,1);
	sem_getvalue(semA,&ValsemA);
	sem_getvalue(semB,&ValsemB);
	sem_getvalue(semC,&ValsemC);
	sem_getvalue(semD,&ValsemD);
	printf("semA = %d \n",ValsemA);
	printf("semB = %d \n",ValsemB);
	printf("semC = %d \n",ValsemC);
	printf("semD = %d \n",ValsemD);
}

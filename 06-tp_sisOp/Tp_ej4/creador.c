#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void)
{
   sem_t * semA ;
   sem_t * semB ;
   sem_t * semC ;
   sem_t * semX ;

   int ValsemA ;
   int ValsemB ;
   int ValsemC ;
   int ValsemX ;
   int intid = shmget(0XA,sizeof(int),IPC_CREAT | IPC_EXCL | 0600);
   int shm01 = shmget (0XA,0,0); //inicializo memoria compartida
   int *looper = (int *) shmat (shm01,0,0);//casteo
   *looper = 0;
   shmdt(looper);//la detacheo ya con el 0 cargado

   sem_unlink("/semA");
   sem_unlink("/semB");
   sem_unlink("/semC");
   sem_unlink("/semX");

   semA = sem_open("/semA",O_CREAT|O_EXCL,0644,1) ;
   semB = sem_open("/semB",O_CREAT|O_EXCL,0644,1) ;
   semC = sem_open("/semC",O_CREAT|O_EXCL,0644,0) ;
   semX = sem_open("/semX",O_CREAT|O_EXCL,0644,0) ;

   sem_getvalue(semA,&ValsemA);
   sem_getvalue(semB,&ValsemB);
   sem_getvalue(semC,&ValsemC);
   sem_getvalue(semX,&ValsemX);

   printf("semA = %d \n",ValsemA);
   printf("semB = %d \n",ValsemB);
   printf("semC = %d \n",ValsemC);
   printf("semX = %d \n",ValsemX);
 
}

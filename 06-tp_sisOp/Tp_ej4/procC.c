#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void)
{
   int shm01 = shmget (0XA,0,0);
   int *looper = (int *) shmat (shm01,0,0);	
   sem_t * semA ;
   sem_t * semB ;
   sem_t * semC ;   
   sem_t * semX ;

   int ValsemA ;
   int ValsemB ;
   int ValsemC ;   
   int ValsemX ;

   semA = sem_open("/semA",0);
   semB = sem_open("/semB",0);
   semC = sem_open("/semC",0);
   semX = sem_open("/semX",0);

   sem_getvalue(semA,&ValsemA);
   sem_getvalue(semB,&ValsemB);
   sem_getvalue(semC,&ValsemC);
   sem_getvalue(semX,&ValsemX);

   printf("semA = %d \n",ValsemA); 
   printf("semB = %d \n",ValsemB);
   printf("semC = %d \n",ValsemC);
   printf("semX = %d \n",ValsemX);

   while(*looper < 20)
   {
     sem_wait(semC);
     sem_wait(semX);
     if(*looper <20){
	   (*looper)++;	 
       printf("Proceso C  \n");
       sleep(1);
     }
     sem_post(semA);
     sem_post(semB);
   }
}

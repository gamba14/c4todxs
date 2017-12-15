#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

void MostrarValorSemaforo(sem_t *,sem_t *);
int looper = 0;

int main(void)
{
   int shm01 = shmget (0XA,0,0);
   int *looper = (int *) shmat (shm01,0,0);
   sem_t * semA ;
   sem_t * semX ;   
   semA = sem_open("/semA",0);
   semX = sem_open("/semX",0);
  
   while(*looper < 20)
   {
  //   MostrarValorSemaforo(semA,semX);
     sem_wait(semA);
     if(*looper <20){
       printf("Proceso A  \n");
       //(*looper)++;
       sleep(1);
       
	 }
     sem_post(semX);
 //    MostrarValorSemaforo(semA,semX);
   }
}

void MostrarValorSemaforo(sem_t * semA,sem_t * semX)
{
   int ValsemA ;
   int ValsemX ;

   sem_getvalue(semA,&ValsemA) ;
   sem_getvalue(semX,&ValsemX) ;
   
   printf("semA = %d ---------- semX = %d\n",ValsemA,ValsemX);
}

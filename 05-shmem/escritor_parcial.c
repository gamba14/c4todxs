
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "operipc.h"

int main(int argc, char ** argv)
{
   char cadena[30];
   strcpy(cadena,"Hola Mundo Cruel\0");
   int semid = semget(0xb,0,0);
   int shmid = shmget(0xb,0,0);
   printf("shmid %d\n",shmid);
   printf("semid %d\n",semid);   
   char * dir ;
   dir = (char *) shmat(shmid,0,0);
   int i = 0 ;
   do
   {
     P(semid,0);
     *dir = cadena[i]  ;
     usleep(50000);
     V(semid,1);
   } while(cadena[i++] != '\0');
   exit(0);
}

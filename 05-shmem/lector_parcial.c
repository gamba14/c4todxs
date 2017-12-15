
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "operipc.h"

int main(int argc, char ** argv)
{
   int semid = semget(0xb,0,0);
   int shmid = shmget(0xb,0,0);
   printf("shmid %d\n",shmid);
   printf("semid %d\n",semid);
   char * dir ;
   dir = (char *) shmat(shmid,0,0);
   
   while(*dir != '\0')
   { 
     P(semid,1);
     printf("%c\n",*dir) ;
     usleep(500000);
     V(semid,0);
   }
   exit(0);
}

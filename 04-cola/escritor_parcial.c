#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mensaje {
                   long tipo_msg;
                   char caracter;
               };

int main(int argc , char *argv[])
{
  char cadena[30] ;   
  strcpy(cadena,"Hola Mundo Cruel\0");
  struct mensaje mimensaje;
  int msgid = msgget(0xa,0);
  int i = 0 ;
  do 
   {
     mimensaje.tipo_msg = 1;
     mimensaje.caracter = cadena[i];
     msgsnd(msgid,&mimensaje,1,0); 
   }while(cadena[i++] != '\0');
   exit(0);
}

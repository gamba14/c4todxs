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
  struct mensaje mimensaje;
  int msgid = msgget(0xa,0);
  msgrcv(msgid,&mimensaje,1,0,0);
  while(mimensaje.caracter != '\0')
  {
    printf("%c",mimensaje.caracter);
    msgrcv(msgid,&mimensaje,1,0,0);
  }
  printf("\n");
  exit(0);
}

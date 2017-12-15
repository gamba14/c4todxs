#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>


int main(int argc , char *argv[]) {
	struct mensaje {
		long tipo_msg;
		char texto_msg[256];
		} mimensaje;
	int msgid = atoi(argv[1]);
	int tam_msg ;
	mimensaje.tipo_msg = 1 ;
	strcpy(mimensaje.texto_msg,"Hola");
	while(!msgsnd(msgid,&mimensaje,256,0));  
	while(1){
				tam_msg = msgrcv(msgid,&mimensaje,256,0,0); 
				printf("tipo  mensaje recibido = %li"  ,mimensaje.tipo_msg);
				mimensaje.texto_msg[tam_msg] = '\0';  
				printf("texto = %s\n",mimensaje.texto_msg);  
			}
	return 0;
}

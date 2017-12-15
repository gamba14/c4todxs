#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg_1{
	long tipo_msg;
	char texto[255];
};

int main(int argc , char *argv[]){
	char cadena[30];
	strcpy(cadena,"R-A-M-O-N-E-S\0");
	struct msg_1 mensaje;
	int msgid= msgget(0xa,IPC_CREAT|0700);
	int i=0;
	do{
		mensaje.tipo_msg = 1;
		mensaje.texto = cadena[i];
		msgsnd(msgid,&mensaje,sizeof(mensaje.texto),0);
	}while(cadena[i++] != '\0');
	exit(0);
}

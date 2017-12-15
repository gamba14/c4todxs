#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msgbuf{
	long tipo_msg;
	char texto;
};

int main(int argc,char **argv){
	struct msgbuf mensaje;
	int i=0,mqid = msgget(0xa,0);
	char linea[30];
	strcpy(linea,"hola amigos\0");
	do{
		mensaje.tipo_msg = 1;
		mensaje.texto = linea[i];
		msgsnd(mqid,&mensaje,1,0);
	}while( linea[i++] != '\0');
	exit(0);
}

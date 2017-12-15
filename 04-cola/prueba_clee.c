#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msgbuf{
	long msg_tipo;
	char texto;
};

int main(int argc, char **argv){
	int mqid = msgget(0xa,0);
	struct msgbuf mensaje;
	msgrcv(mqid,&mensaje,1,0,0);
	while(mensaje.texto != '\0'){
		printf("%c",mensaje.texto);
		msgrcv(mqid,&mensaje,1,0,0);
	}
	exit(0);
}

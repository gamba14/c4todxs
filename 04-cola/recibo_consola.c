#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

struct msgbuf{
	long msg_tipo;
	char texto[256];
};

int main( int argc, char **argv){
	struct msgbuf mensaje;
	int msgid = msgget(0XA,0);
	msgrcv(msgid,&mensaje,1,0,0);
	while(mensaje.texto != '\0'){
		printf("%c\n",mensaje.texto);
		msgrcv(msgid,&mensaje,1,0,0);
		sleep(1);
	}
	exit(0);
}


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

struct msgrecib{
	long tipo_msg;
	char texto[1];
};

int main(int argc, char *argv[]){
	struct msgrecib mensaje;
	int msgid = msgget(0xa,0);
	msgrcv(msgid,&mensaje,1,0,0);
	printf("recibo mensaje desde el mas alla \n");
	while(mensaje.texto != '\0'){
		printf("%c",mensaje.texto);
		msgrcv(msgid,&mensaje,1,0,0);
		sleep(1);
	}
	printf("\n");
	exit(0);
}
	
	

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

struct msgenvio{
	long tipo_msg;
	char texto;
};

int main(int argc, char **argv){
	char cadena[] = "hola amigos\0";
	struct msgenvio mensaje;
	int msgid = msgget(0XA,0);
	printf("%d\n",msgid);
	//strcpy(cadena,"Hola\0");
	mensaje.tipo_msg = 1;
	mensaje.texto = cadena;
	msgsnd(msgid,&mensaje,sizeof(cadena),0);
	exit(0);
}
	
	
	

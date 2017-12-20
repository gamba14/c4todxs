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
	char texto[30];
};

int main(int argc, char **argv){
	struct msgenvio mensaje;
	int msgid = msgget(0XA,0);
	printf("%d\n",msgid);
	gets(mensaje.texto);
	mensaje.tipo_msg = 1;
	msgsnd(msgid,&mensaje,sizeof(mensaje.texto),0);
	exit(0);
}
	
	
	

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char *argv[]){
	key_t key;
	int msgid;
	msgid = msgget(0xa,IPC_CREAT | IPC_EXCL | 0644);
	printf("cola de mensajes con clave %x identificador %d\n",key,msgid);
	system("ipcs");
	exit(0);	
}


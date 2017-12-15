#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	msgget(0xa,IPC_CREAT|IPC_EXCL|0600);
}

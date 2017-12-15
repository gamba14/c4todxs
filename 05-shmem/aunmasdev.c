#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

int main(int argc,char **argv){
	int shmid = shmget(0xa,0,0);
	char * variable;
	variable = (char *) shmat(shmid,0,0);
	printf("la variable leida de la shm es %s\n",variable);
	exit(0);
}

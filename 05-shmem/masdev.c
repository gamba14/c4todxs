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

int main(int argc, const char **argv){
	system("sh kill_ipcs.sh");
	int shmid = shmget(0xa,1,IPC_CREAT|IPC_EXCL|0600);
	char * variable;
	variable = (char *) shmat(shmid,0,0);
	(*variable) = *argv[1];
	shmdt(variable);
	system("./aunmasdev");
	exit(0);
}

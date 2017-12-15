#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "operipc.h"

int main(int argc, char **argv){
	int retval = semget(0xA,0,0);
	int retval2 = shmget(0xA,0,0);	
	while(1){
		P(retval,1);
		P(retval,3);
		int *num1 = (int*) shmat(retval2,0,0);
		printf("recibi de productor %d\n", num1);
		sleep(1);
		V(retval,0);
		V(retval,2);
	}
}

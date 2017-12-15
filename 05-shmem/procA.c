#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "operipc.h"

int main(int argc, char **argv){
	
	int retval = semget(0xA,0,0);
	int retval2 = shmget(0xA,0,0);
	int *num1 = (int *) shmat(retval2,0,0);	
		
	while(*num1 < 50){
		P(retval,0);		
		int *num1 = (int *) shmat(retval2,0,0);		
		(*num1)++;
		//shmdt(num1);
		sleep(1);
		V(retval,3);
	}
	
}


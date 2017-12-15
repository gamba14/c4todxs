#include <stdio.h>
#include <stdlib.h>

int main(){
	int pid;
	pid = fork();
	printf("%d \n",pid);
}

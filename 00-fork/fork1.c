#include <stdio.h>
#include <unistd.h>

int main(){
	fork();
	printf("quien soy?, el padre o el hijo?\n");
	exit(0);
	}

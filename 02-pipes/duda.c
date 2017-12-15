#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	int p[2];
	pipe(p);
	char letrain = 'a';
	char letraout;
	while(letrain != 'z'){
		write(p[1],&letrain,1);
		while(read(p[0],&letraout,1) > 0)
		printf("letra out %c\n",letraout);
		letrain ++;
	}
	close(p[1]);
	close(p[0]);
}

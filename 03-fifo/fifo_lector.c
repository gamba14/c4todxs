#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd = open("mififo",O_RDONLY);
	char mensaje[255];
	read(fd,mensaje,255);
	printf("%s",mensaje);
	close(fd);
}

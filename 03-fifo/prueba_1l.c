#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){
	int retval = mkfifo("fifoprueba2",O_CREAT|0777);
	int fd = open("fifoprueba1",O_RDONLY);
	int fd2 = open("fifoprueba2",O_WRONLY);
	char linea[255];
	char rta[255];
	do{
		read(fd,linea,255);
		printf(">>>%s\n",linea);
		strfry(linea);
		write(fd2,linea,strlen(linea)+1);
	}while(strcmp(linea,"abort") != 0);
	close(fd);
	exit(0);
}

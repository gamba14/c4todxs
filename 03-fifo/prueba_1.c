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
	int retval = mkfifo("fifoprueba1",O_CREAT|0777);
	if(retval == 0)printf("Fifo creado\n");
	char linea[255];
	char rta[255];
	int fd = open("fifoprueba1",O_WRONLY);
	int fd2 = open("fifoprueba2",O_RDONLY);
	do{
		printf("<<<");
		gets(linea);
		write(fd,linea,strlen(linea)+1);
		usleep(500);
		read(fd2,rta,255);
		printf(">>>%s\n",rta);
	}while((strcmp(linea,"abort")) != 0);
	close(fd);
	exit(0);
}

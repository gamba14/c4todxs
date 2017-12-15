#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>



int main(int argc, char *argv[]){
	sem_t *sem1;
	sem_unlink("/sem1");		
	mkfifo("mififo",O_CREAT|0777);
	char cadena[255];
	sem1 = sem_open("/sem1",O_CREAT|O_EXCL,0777,0);
	strcpy(cadena,"Hola,esto es una prueba\0");
	int fd = open("mififo",O_WRONLY);
	int i =0;
	do{	
		sem_wait(sem1);
		char caracter = cadena[i];
		write(fd,caracter,strlen(caracter));
		sem_post(sem1);
	}while(cadena[i++] != '\0');
	close(fd);
}

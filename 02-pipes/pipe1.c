#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
	
	int p[2];
	int retval1 = pipe(p);
	pid_t pid;
	char buf;
	
	if(retval1 < 0){
		printf("ERROR AL CREAR PIEPE\n");
	}
	
	pid = fork();
	
	if(pid > 0){
		system("clear");
		//estoy en el proceso padre y quiero escribir en el pipe
		close(p[0]);//ciero el extremo lector
		write(p[1],argv[1],strlen(argv[1]));//escribo en el pipe
		close(p[1]);//cierro el extremo escritor marco el EOF
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	else{
		//estoy en el proceso hijo
		close(p[1]);//cierro el extremo escritor
		while(read(p[0],&buf,1)>0){
			write(STDOUT_FILENO,&buf,1);
			usleep(50);
		}
		write(STDOUT_FILENO,"\n",1);
		close(p[0]);//cierro extremo lector
	}
}
		



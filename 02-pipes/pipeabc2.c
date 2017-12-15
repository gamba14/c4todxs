/* En este codigo muestro que cuando un proceso hijo finaliza su ejecucion
 * es decir, cierra el canal de escritura, el proceso retenido en read se 
 * desbloquea y continua con su curso normal
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	int p[2];
	pid_t pid;
	pipe(p);
	pid = fork();
	if (pid > 0){
		//el proceso padre leera del proceso hijo
		char recibi;
		close(p[1]);
		while((read(p[0],&recibi,1)) > 0){
			printf("recibi de hijo %c\n",recibi);
			sleep(1);
		}
		printf("termino el proceso escritor\n");
		getchar();
	}
	else{
		close(p[0]);
		char mando = 'a';
		while( mando <= 'g'){
			write(p[1],&mando,1);
			mando ++;
			sleep(1);
		}
		close(p[1]);
	}
		
}

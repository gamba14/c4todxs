/* en este codigo, lo que tratare de mostrar es lo
 * que sucede cuando un proceso lector cierra el canal
 * y el proceso escritor todavia no termino de escribir
 * El sistema operativo mata el proceso
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc,char **argv){
	int p[2];
	char letra, envio = 'a';
	pipe(p);
	pid_t pid;
	pid = fork();
	if(pid ==0){
		close(p[1]);
		while((read(p[0],&letra,1)) > 0){
			printf("recibi %c\n",letra);
			sleep(1);
			if(letra == 'h'){
				close(p[0]);
				}			
		}
	}
		else{
			// el padre envia al hijo
			close(p[0]);
			while(envio < 'z'){
				write(p[1],&envio,1);
				envio ++;
				sleep(1);
			}
			close(p[1]);
		}
}

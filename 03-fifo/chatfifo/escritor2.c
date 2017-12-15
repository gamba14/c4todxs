//      escritor2.c
//      
//      Copyright 2011 grchere <grchere@debian2>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid;
	pid = fork();
	if ( pid > 0 ) { // estoy en el padre
		int status;
		int fd = open("/tmp/fifo2",O_WRONLY);
		char entrada[512];
		do {
			printf("escritor2 envio:");
			memset(entrada,0,512);
			gets(entrada);
			write(fd,entrada,strlen(entrada)+1);
		} while(strcmp(entrada,"chau"));
		close(fd);
		wait(&status);

	} else { // estoy en el hijo

		int i,lei;
		char byte;
		int fd = open("/tmp/fifo1",O_RDONLY);
		char entrada[512];
		do {
			printf("hijo2 leyendo fifo1:");
			memset(entrada,0,512);
			i=0;
			while ( (lei = read(fd,&byte,1)) && byte != '\0' && i < 512 ) {
				entrada[i++]=byte;
			}
			printf("%s\n",entrada);
		} while(strcmp(entrada,"chau"));
		close(fd);

	}
	return 0;
}


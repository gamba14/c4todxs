//      lector2i.c
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
	int i=0,lei;
	char byte;
	int fd;
	// espera activa
	while( (fd = open("/tmp/fifo1",O_RDONLY | O_NONBLOCK) ) == -1)
		printf("lector2i espera activa %d\n",i++);
	
	printf("lector2i is alive!\n");
	char entrada[512];
	do {
		printf("lector2i leyendo fifo1:");
		memset(entrada,0,512);
		i=0;
		while ( (lei = read(fd,&byte,1)) && byte != '\0' && i < 512 ) {
			entrada[i++]=byte;
		}
		printf("%s\n",entrada);
	} while(strcmp(entrada,"chau"));
	close(fd);
	// recupero pid de escritor2i
	int pid;
	FILE *f = fopen("/tmp/escritor2i.txt","r");
	fscanf(f,"%d",&pid);
	fclose(f);
	printf("el pid de escritor2i es %d\n",pid);
	kill((pid_t) pid,SIGUSR1);
	return 0;
}


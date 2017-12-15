//      escritor2i.c
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
	FILE *f = fopen("/tmp/escritor2i.txt","w");
	fprintf(f,"%d",(int) getpid());
	fclose(f);
	int fd,i=0;
	// espera activa
	while( (fd = open("/tmp/fifo2",O_WRONLY | O_NONBLOCK) ) == -1)
		printf("escritor2i espera activa %d\n",i++);
	printf("escritor2i is alive!\n");
	char entrada[512];
	do {
		printf("escritor2i envio:");
		memset(entrada,0,512);
		gets(entrada);
		write(fd,entrada,strlen(entrada)+1);
	} while(strcmp(entrada,"chau"));
	close(fd);
	pause();
	return 0;
}


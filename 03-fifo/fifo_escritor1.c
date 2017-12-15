/*
 * fifo_yin1.c
 * 
 * Copyright 2017 grchere <grchere@debian2>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/*
 * Creamos FIFO desde programa usando llamada mkfifo()
 * Proceso escritor, no sabemos cual proceso se ejecuta primero
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd,ret;
	char linea[255];
	
	ret = mkfifo("yin1",O_CREAT|0777);
	if ( ret == -1 ) {
		printf("Error en la creacion del FIFO yin1\n");
		if ( errno == EEXIST ) {
			printf("El FIFO yin1 ya existe!\n");
			fd = open("yin1",O_WRONLY);
		} else {
			printf("Error en apertura de yin1, no puedo continuar\n");
			exit(1);
		}
	} else {
		printf("El FIFO yin1 creado OK! ret=%d\n",ret);
		fd = open("yin1",O_WRONLY);
	}
	printf("El file descriptor de yin1 vale %d\n",fd);
	do {
		printf(">>");
		gets(linea);
		write(fd,linea,strlen(linea)+1);
	} while(strcmp(linea,"chau") != 0);
	close(fd);
	
	return 0;
}


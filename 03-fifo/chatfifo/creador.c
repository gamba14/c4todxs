//      creador.c
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
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int fd;
	fd =  mkfifo ( "/tmp/fifo1", 0600 );
	if ( fd != -1 ) {
		fd =  mkfifo ( "/tmp/fifo2", 0600 );
		if ( fd != -1 ) {
			printf("fifo1 y fifo2 creado Ok!\n");
		} else {
			perror("Error creando /tmp/fifo2");
		}
	} else {
		perror("Error creando /tmp/fifo1");
	}
	return 0;
}


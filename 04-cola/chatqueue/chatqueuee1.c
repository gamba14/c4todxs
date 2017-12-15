//      chatqueuee1.c
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
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

/* proceso escritor1 de cola de mensaje para chat */
struct mensaje {
   long tipo;
   char mensa[512];
} mensaje;

int main(int argc, char **argv) {
	int msgid = msgget(0xA,0);
	pid_t pid = fork();
	struct mensaje m;
	if ( pid > 0 ) {
		// codigo del padre
		int status=0;
		m.tipo = 1L;
		do {
			memset(m.mensa,0,512);
			printf("Envio (1):");
			fgets(m.mensa, 512, stdin);
			msgsnd(msgid,&m,sizeof(m.mensa)-sizeof(long),0); 
		} while(strncmp(m.mensa,"chau",4));
		wait(&status);
	} else {
		// codigo del hijo
		m.tipo = 2L;
		do {
			memset(m.mensa,0,512);
			printf("Recibo (2):");
			msgrcv(msgid,&m,sizeof(m)-sizeof(long),m.tipo,0);
			printf("%s\n",m.mensa); 
		} while(strncmp(m.mensa,"chau",4));
	}
	return 0;
}


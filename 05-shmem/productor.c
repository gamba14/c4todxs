/*
 * productor.c
 * 
 * Copyright 2017 Agustin <gambirassi.a@gmail.com>
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
 * 
 * 
 */
/* este es el ejemplo del productor consumidor
 * implementado en C del capitulo 6 del libro de 
 * silberchatz
 */
 
 #include "operipc.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/shm.h>
 #include <sys/ipc.h>
 #define BUFF_SIZE 5 
 char productor(void);
 
 int main(int argc,char **argv){
	 system("sh kill_ipcs.sh");
	 system("./init_prodcons");
	 //creo las areas de memoria compartida
	 //para el buffer y para el contador.
	 int buffershm = shmget(0xa,0,0);
	 int contadorshm = shmget(0xb,0,0);
	 int semid = semget(0xa,0,0);
	 
	 int *contador,pone =0;
	 contador = (int *) shmat(contadorshm,0,0);
	 char * buffer;
	 buffer = (char *) shmat(buffershm,0,0);
	 
	 while(1){
		 while(*contador != BUFF_SIZE){
			 P(semid,0);
			 buffer[pone] = productor();
			 (*contador)++;
			 printf("Productor: ""\x1b[32m""Produjo %c\n""\x1b[0m",buffer[pone]);
			 pone = (pone +1)%BUFF_SIZE;
			 V(semid,0);
		 }		 
	 }
	 
} 

char productor(void){
	static int letra = 'a'-1;
	if(letra == 'z'){
		letra = 'a';
		}
	else{
		letra ++;
		return letra;
		
	}
}

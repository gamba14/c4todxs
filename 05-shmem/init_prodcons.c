/*
 * init_prodcons.c
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

#include "operipc.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/shm.h>
 #include <sys/ipc.h>
 
 int main(int argc, char **argv){

		int buffershm = shmget(0xa,5,IPC_CREAT|IPC_EXCL|0777);
		int contadorshm = shmget(0xb,sizeof(int),IPC_CREAT|IPC_EXCL|0777);	 
		int *contador;
		int semid = semget(0xa,1,IPC_CREAT|IPC_EXCL|0666);
		semctl(semid,0,SETVAL,1);
		contador = shmat(contadorshm,0,0);
		*contador = 0;
		printf("TODO OK\n""\x1b[33m""Semaforo: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",semid);
		printf("\x1b[33m""Contador: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",contadorshm);
		printf("\x1b[33m""Buffer: ""\x1b[0m""\x1b[32m""%d""\x1b[0m""\n",buffershm);
		exit(0);
	}

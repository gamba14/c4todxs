#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

//prototipo de funciones, voy a trabajar con 3 hilos

void* hiloA();
void* hiloB();
void* hiloC();
sem_t semA,	semB,semC,semX;

int main(int argc , char **argv){
	pthread_t thA,thB,thC;	
	sem_init(&semA,0,1);
	sem_init(&semB,0,1);
	sem_init(&semC,0,0);
	sem_init(&semX,0,0);
	//lanzo los hilos
	pthread_create(&thA,NULL,hiloA,NULL);
	pthread_create(&thB,NULL,hiloB,NULL);
	pthread_create(&thC,NULL,hiloC,NULL);
	//hago join para esperar a que terminen los hilos
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	pthread_join(thC,NULL);
	//fin de los join
	exit(0);
}

void *hiloA(){
	while(1){
		sem_wait(&semA);
		printf("SC : A\n");
		sleep(1);
		sem_post(&semX);
	}
}

void *hiloB(){
	while(1){
		sem_wait(&semB);
		sem_wait(&semX);
		printf("SC : B\n");
		sleep(1);
		sem_post(&semA);
		sem_post(&semC);
	}
}

void *hiloC(){
	while(1){
		sem_wait(&semC);
		sem_wait(&semX);
		printf("SC : C\n");
		sleep(1);
		sem_post(&semA);
		sem_post(&semB);
		}
	
}


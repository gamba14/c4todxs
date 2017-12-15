#include <stdlib.h>
#include <stdout.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

//prototipo de funciones

void *hiloA();
void *hiloB();
void *hiloC();

sem_t semA,semX;

int main(int arcv, char **argv){
	
	pthread_t thA,thB,thC;
	
	sem_init(&semA,0,1);
	sem_init(&semX,0,0);
	
	pthread_create(&thA,NULL,hiloA,NULL);
	pthread_create(&thB,NULL,hiloB,NULL);
	pthread_create(&thc,NULL,hiloC,NULL);
	
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	pthread_join(thC,NULL);
	
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
		sem_wait(&semX);
		printf("SC : B\n");
		sleep(1);
		
	}
}

void *hiloC(){
	while(1){
	}
}



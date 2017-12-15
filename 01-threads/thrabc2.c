#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *hiloA();
void *hiloB();
void *hiloC();

pthread_mutex_t semA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t semC = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv){
	//bloqueo semB y semC
	pthread_mutex_lock(&semB);
	pthread_mutex_lock(&semC);
	//lanzo los hilos
	pthread_t thA,thB,thC;
	pthread_create(&thA,NULL,hiloA,NULL);
	pthread_create(&thB,NULL,hiloB,NULL);
	pthread_create(&thC,NULL,hiloC,NULL);
	//hago join esperando a terminar los hilos
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	pthread_join(thC,NULL);
	
	exit(0);
}

void *hiloA(){
	while(1){
		pthread_mutex_lock(&semA);
		printf("SC : A\n");
		sleep(1);
		pthread_mutex_unlock(&semB);
	}
}

void *hiloB(){
	while(1){
		pthread_mutex_lock(&semB);
		printf("SC : B\n");
		sleep(1);
		pthread_mutex_unlock(&semC);
	}
}

void *hiloC(){
	while(1){
		pthread_mutex_lock(&semC);
		printf("SC : C\n");
		sleep(1);
		pthread_mutex_unlock(&semA);
	}
}

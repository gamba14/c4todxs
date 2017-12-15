#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* hiloA();
void* hiloB();
void* hiloC();

pthread_mutex_t semA = PTHREAD_MUTEX_INITIALIZER;//SemA = 1
pthread_mutex_t semB = PTHREAD_MUTEX_INITIALIZER;//Semb = 1
pthread_mutex_t semC = PTHREAD_MUTEX_INITIALIZER;//SemC = 1
pthread_mutex_t semX = PTHREAD_MUTEX_INITIALIZER;//SemX = 1

int main(int argc, char **argv){
	//bloqueo semC y semX
	pthread_mutex_lock(&semC);// semC = 0
	pthread_mutex_lock(&semX);// semX = 0
	
	pthread_t th1,th2,th3;
	
	printf("Se lanzan los hilos A,B,C\n");
	
	pthread_create(&th1,NULL,hiloA,NULL);
	pthread_create(&th2,NULL,hiloB,NULL);
	pthread_create(&th3,NULL,hiloC,NULL);
	
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	
	exit(0);
}

void *hiloA(){
	while(1){
		pthread_mutex_lock(&semA);//P o wait
		printf("SC : A\n");
		sleep(1);
		pthread_mutex_unlock(&semX);//V o signal		
	}
}

void *hiloB(){
	while(1){
		pthread_mutex_lock(&semB);//P o wait
		pthread_mutex_lock(&semX);//P o wait
		printf("SC : B\n");
		sleep(1);
		pthread_mutex_unlock(&semA);//V o signal
		pthread_mutex_unlock(&semC);//V o signal
	}
}

void *hiloC(){
	while(1){
		pthread_mutex_lock(&semC); //P o wait
		pthread_mutex_lock(&semX);//P o wait
		printf("SC : C\n");
		sleep(1);
		pthread_mutex_unlock(&semA);//V o signal
		pthread_mutex_unlock(&semB);//V o signal
	}
}

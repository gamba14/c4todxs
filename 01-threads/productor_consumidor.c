#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t semEmpty,semFull,semMutex;
void *productor();
void *consumidor();
char buf[8];

int main(int argc, char **argv){
	pthread_t thP,thC;	
	
	sem_init(&semEmpty,0,8);
	sem_init(&semFull,0,0);
	sem_init(&semMutex,0,1);
	
	pthread_create(&thP,NULL,productor,NULL);
	pthread_create(&thC,NULL,consumidor,NULL);
	
	pthread_join(thP,NULL);
	pthread_join(thC,NULL);
	
	}
	
void *productor(){
	int i = 0;
	while(1){		
		char letra = 'a';
		sem_wait(&semEmpty);
		sem_wait(&semMutex);
		while(i < 8){
			printf("PRODUCTOR: %c\n",letra);
			buf[i++]=letra;
			letra ++;
			sleep(1);
		}
		sem_post(&semMutex);
		sem_post(&semFull);	
		}			
}

void *consumidor(){
	while(1){	
	sem_wait(&semFull);
	sem_wait(&semMutex);
	for(int i = 0;i<8;i++){
		printf("%s\n",&buf[i]);
		sleep(1);
	}
	sem_post(&semMutex);
	sem_post(&semEmpty);
}
}


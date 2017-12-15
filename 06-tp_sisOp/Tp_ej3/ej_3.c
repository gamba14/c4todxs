#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// prototipo de funciones (hilos)
void *hiloA(void *);
void *hiloB(void *);
void *hiloC(void *);

// declaro los mutex globales a utilizar
pthread_mutex_t mA = PTHREAD_MUTEX_INITIALIZER; // SemA=1
pthread_mutex_t mB = PTHREAD_MUTEX_INITIALIZER; // SemB=1
pthread_mutex_t mC = PTHREAD_MUTEX_INITIALIZER; // SemC=1
pthread_mutex_t mX = PTHREAD_MUTEX_INITIALIZER; // SemX=1

int looper = 0;

int main(int argc, char **argv) {	
	
	pthread_t thA,thB,thC;
	
	pthread_mutex_lock(&mC);  // SemC=0
	pthread_mutex_lock(&mX);  // SemX=0	
	
	pthread_create(&thA,NULL,hiloA,NULL);
	pthread_create(&thB,NULL,hiloB,NULL);
	pthread_create(&thC,NULL,hiloC,NULL);
	
	pthread_join(thA,NULL);
	pthread_join(thB,NULL);
	pthread_join(thC,NULL);
	
	printf("main(): fin hago join(), finalizaron los hilos!\n");

	return 0;
}

// implemento hilo A
void *hiloA(void *p) {	
	while(looper < 20) {		
		pthread_mutex_lock(&mA);  
		if(looper < 20){			
						printf("A\n");
						sleep(1);
		}
		pthread_mutex_unlock(&mX); 
	}
	printf("Termino hilo A\n");	
	pthread_exit(NULL);  
	
}

// implemento hilo B
void *hiloB(void *p) {	
	while(looper < 20) {
		pthread_mutex_lock(&mB);  // P(semB)      wait(SemB)
		pthread_mutex_lock(&mX);  // P(semX)      wait(SemX)
		if(looper < 20){			
						printf("B\n");
						sleep(1);
		}				
		pthread_mutex_unlock(&mC); // V(semC)     signal(SemC)
		pthread_mutex_unlock(&mA); // V(semA)     signal(SemA)
	}
	printf("Termino Hilo B\n");
	pthread_exit(NULL);  // nunca se ejecuta esto!
}

// implemento hilo C
void *hiloC(void *p) {	
	while(looper < 20) {		
		pthread_mutex_lock(&mC);  // P(semC)      wait(SemC)
		pthread_mutex_lock(&mX);  // P(semX)      wait(SemX)
		printf("C\n");
		looper++;
		sleep(1);
		pthread_mutex_unlock(&mB); // V(semB)     signal(SemB)
		pthread_mutex_unlock(&mA); // V(semA)     signal(SemA)
	}
	printf("Termino hilo C\n");
	pthread_exit(NULL);  // nunca se ejecuta esto!
}


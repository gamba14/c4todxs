#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *hiloA(void *,int *loops);
void *hiloB(void *,int *loops);
void *hiloC(void *,int *loops);

pthread_mutex_t mA = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mB = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mC = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mX = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv){
	int loops = atoi(argv[1]),i=0;
	
		pthread_t thA,thB,thC;
	
		printf("main(): lock SemC,SemX\n");

		pthread_mutex_lock(&mC);  // SemC=0
		pthread_mutex_lock(&mX);  // SemX=0
	
		printf("main(): lanzo los hilos A,B,C\n");
		pthread_create(&thA,NULL,hiloA,(void *,int *loops));//probar con el create, cuarto argumento.
		pthread_create(&thB,NULL,hiloB,*loops);
		pthread_create(&thC,NULL,hiloC,*loops);

		printf("main(): hago join() esperando la finalizacion de los hilos\n");
		pthread_join(thA,NULL);
		pthread_join(thB,NULL);
		pthread_join(thC,NULL);				
		printf("main(): fin hago join(), finalizaron los hilos!\n");
	
}

// implemento hilo A
void *hiloA(void *p) {
	int loops *i j;
	i = (int loops*) p;
	j=0;
	while(j<i) {
		i++;
		pthread_mutex_lock(&mA);  // P(semA)      wait(SemA)
			printf("hiloA: SC!\n");
			sleep(1);
		pthread_mutex_unlock(&mX); // V(semX)     signal(SemX)
	}
	pthread_exit(NULL);  // nunca se ejecuta esto!
}

// implemento hilo B
void *hiloB(void *p) {
	while(i<3) {
		i++;
		pthread_mutex_lock(&mB);  // P(semB)      wait(SemB)
		pthread_mutex_lock(&mX);  // P(semX)      wait(SemX)
			printf("hiloB: SC!\n");
			sleep(1);
		pthread_mutex_unlock(&mC); // V(semC)     signal(SemC)
		pthread_mutex_unlock(&mA); // V(semA)     signal(SemA)
	}
	pthread_exit(NULL);  // nunca se ejecuta esto!
}

// implemento hilo C
void *hiloC(void *p) {
	while(i<3) {
		i++;
		pthread_mutex_lock(&mC);  // P(semC)      wait(SemC)
		pthread_mutex_lock(&mX);  // P(semX)      wait(SemX)
			printf("hiloC: SC!\n");
			sleep(1);
		pthread_mutex_unlock(&mB); // V(semB)     signal(SemB)
		pthread_mutex_unlock(&mA); // V(semA)     signal(SemA)
	}
	pthread_exit(NULL);  // nunca se ejecuta esto!
}



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void *fnthr1();
void *fnthr2();
//void *fnthr3();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

int main(int argc, char **argv){
	
	pthread_t thr1,thr2;//,thr3;
	
	printf("Lanzo los hilos 1,2\n");
	
	pthread_create(&thr1,NULL,fnthr1,NULL);
	pthread_create(&thr2,NULL,fnthr2,NULL);
	//pthread_create(&thr3,NULL,fnthr3,NULL);
	
	pthread_join(thr1,NULL);
	pthread_join(thr2,NULL);
	//pthread_join(thr3,NULL);
	
	printf("terminaron los hilos, saliendo\n");
	
	exit(0);
}

void *fnthr1(){
	for(int i=0;i<20;i++){
		pthread_mutex_lock(&mutex1);
		count ++;
		printf("soy el thr1 y mi valor de i es %d\n",count);
		pthread_mutex_unlock(&mutex1);
		sleep(1);
	}
	pthread_exit(0);
}
void *fnthr2(){
	for(int i=0;i<20;i++){
		pthread_mutex_lock(&mutex1);
		count++;
		printf("soy el thr2 y mi valor de i es %d\n",count);
		pthread_mutex_unlock(&mutex1);
		sleep(1);
	}
		pthread_exit(0);
}

/*void *fnthr3(){
		pthread_mutex_lock(&mutex2);
		count++;
		printf("soy el thr3 y mi valor de i es %d\n",count);
		pthread_mutex_unlock(&mutex2);
		pthread_exit(0);
}
	*/

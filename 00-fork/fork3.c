#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
	pid_t pid;
	int a = 20;
	printf("soy el proceso padre %d\n",getpid());
	pid = fork();
	if( pid > 0){
		//estoy en el padre
		pid = fork();
		if (pid == 0){
			//estoy en el hijo2
			pid = fork();
			if(pid > 0){
				a--;
				printf("Soy el proceso %d, hijo de %d y a vale %d\n",getpid(),getppid(),a);
			}
			else{
				//estoy en el nieto2
				a--;
				printf("Soy el proceso %d, hijo de %d y a vale %d\n",getpid(),getppid(),a);			}

		}
	}
	else{
		pid = fork();
		if (pid >0){
			//estoy en el hijo1
			a--;
			printf("Soy el proceso %d, hijo de %d y a vale %d\n",getpid(),getppid(),a);
		}

		else{
			a--;
			printf("Soy el proceso %d, hijo de %d y a vale %d\n",getpid(),getppid(),a);
		}
	}
		
			
	return 1;
		
}
		

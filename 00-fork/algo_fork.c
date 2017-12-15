#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
main()

{

   int status, i,nprocesos;
   pid_t childpid;	
   nprocesos = 5;
   for (i = 0; i < nprocesos; ++i) {
     if ((childpid = fork()) < 0) {
       perror("fork:");
       exit(1);
     } 
     // Codigo que ejecutaran los hijos
     if (childpid == 0) { 
       printf("Soy el hijo con pid %ld\n", getpid());
       exit(0); 
     }
   }
   // El padre espera por todos los hijos que creo.
   for (i = 0; i < nprocesos; ++i) 
     wait(&status);
   printf("El padre termina\n");

}

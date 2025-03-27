#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
		
	pid_t me, childpid, asdf;
	me = getpid(); // me va a guardar el valor del de pid de los procesos...
	printf("%d\n", me); // imprimir el pid de un proceso
	childpid = fork(); // variable childpid guarda el valor que retorna fork
	
	if(childpid == 0) // Si el fork que se hace es un hijo...
	{
		printf("Proceso hijo: pronto a llamar a exec().\n");
		asdf = getpid();
		printf("%d\n", asdf);
		execlp("./wazza","",NULL);
		printf("Proceso hijo: exec() terminado.\n");
	}
	else if(childpid > 0) // Si es padre...
	{
		printf("Proceso padre: el PID del proceso hijo es: %d\n", childpid);
		wait(NULL);
	}
	
	printf("Sugar daddy: El proceso hijo termino.\n");
	
	return 0;
}

 // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT // OUTPUT

// ------ PADRE ------

// Se imprime en este orden... 
// Print (me)
// Va al else if del proceso padre, e indica el childpid del padre (ocupando la variable childpd que es igual a fork)
// wait(NULL) esto hace que el padre espere que se ejecute lo del hijo.. ahora se ejecuta lo del hijo.

// ------ HIJO ------

// proceso hijo pronto a llamar a exec
// 


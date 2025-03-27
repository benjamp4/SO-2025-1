#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
		
	int status; // valor entero de status
	pid_t me, childpid; // pid_t que tomará nombre de m y childpid
	me = getpid(); // me es igual a una variable que guardará los valores de getpid
	printf("%d\n", me); // Imprimir el pid del proceso...
	childpid = fork(); // FORK
	
	if(childpid == 0) // HIJO
	{
		printf("Proceso hijo: Ejecutando.\n"); // Ejecuta al hijo
		printf("Bienvenidos a Temuco.\n"); // Bienvenidos a temuco
		exit(9); // exit... termina la ejecucion del proceso (Status 9, se lo pasa al padre para despues mostrar el mensaje de status 9)
	}
	else if(childpid > 0) // PADRE
	{
		printf("Proceso padre: el PID del proceso hijo es: %d\n", childpid); // Valor de fork del padre 
		wait(&status); // Wait... Espera a que termine el hijo para seguir funcionando
	}
	
	printf("Sugar daddy: El proceso hijo termino.\n");
	printf("Status de salida: %d\n", WEXITSTATUS(status)); // Muestra el estado de exit 9
	
	return 0;
}




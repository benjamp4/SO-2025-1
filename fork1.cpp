#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    pid_t pid = fork();  // Llamada a fork, creando el proceso hijo

    // EL PROGRAMA SE PARTE EN DOS, POR ESTO SE PUEDE EJECUTAR EL IF O ELSE AL MISMO TIEMPO, Y NO UNO DESPUES DE OTRO.

    if (pid == 0) {  // Este bloque se ejecuta con el proceso hijo, es ejecutado por el proceso hijo al mismo tiempo que el else.
        cout << "Soy el proceso hijo. Mi PID es " << getpid() << endl;
        cout << "El valor que devuelve fork en el proceso hijo es 0, vease a continuación: " << pid << endl;  // Esto será 0
    } 
    
    else {  // Este bloque se ejecuta con el proceso padre, es ejecutado por el proceso hijo al mismo tiempo que el if.
        cout << "Soy el proceso padre, tengo un PID asignado por el sistema y es: " << getpid() << endl;
        cout << "El valor que devuelve fork en el proceso padre que será igual al PID de mi hijo, vease a continuación: " << pid << endl;  // Este es el PID del hijo
    }

    return 0;
}

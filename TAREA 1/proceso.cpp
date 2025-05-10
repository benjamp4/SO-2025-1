#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>

using namespace std;

#ifndef PROCESO_H
#define PROCESO_H

typedef struct {
    int id;             
    int tiempoLlegada;  
    int burst;          
} Proceso;

#endif

int main() {
    const char* fifo_path = "./miPipe"; // ruta de archivo de la pipe
    mkfifo(fifo_path, 0666); // creando pipe

    cout << "Abriendo pipe en modo escritura" << endl;
    int fifo_pipe = open(fifo_path, O_WRONLY);

    if (fifo_pipe == -1) { // verificar si hubo un error al abrir la pipe
        perror("Error fifo para escritura");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL) + getpid()); // seed aleatoria para crear un numero aleatorio
    int tareasCreadas = (rand() % 4) + 3; // Generar un número aleatorio de tareas entre 3 y 6
    cout << "Enviando tareas" << endl;

    // crear y enviar tareas al planificador
    for (int i = 0; i < tareasCreadas; i++) { // for para cantidad de tareas creadas
        Proceso tareaCreada; 
        tareaCreada.id = getpid() + i;   // se le asigna un id  
        tareaCreada.burst = (rand() % 5) + 1; // Generar un tiempo de CPU aleatorio entre 1 y 5 segundos

        // Enviar la tarea a la pipe
        write(fifo_pipe, &tareaCreada, sizeof(Proceso)); 

        cout << "Proceso " << getpid() << " envió la tarea " << tareaCreada.id << " (CPU burst: " << tareaCreada.burst << " segundos)" << endl;
    }
    
    cout << "Me duermo un ratito..." << endl;
    sleep((rand() % 3) + 1); // dormir entre 1 y 3 segundos antes de terminar

    cout << "Se cierra la pipe..." << endl;
    close(fifo_pipe);
    cout << "Unlinkeando pipe..." << endl;
    unlink(fifo_path);

}

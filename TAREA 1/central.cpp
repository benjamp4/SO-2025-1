#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctime>
#include <cstdlib> 
#include <queue>
#include <chrono>  

using namespace std;

#ifndef PROCESO_H
#define PROCESO_H

typedef struct { // se define la estructura del proceso
    int id;
    int tiempoLlegada;
    int burst;
} Proceso;

#endif

int main() {
    const char* fifo_path = "./miPipe"; // ruta de archivo mi pipe
    mkfifo(fifo_path, 0666);
    
    queue<Proceso> colaProcesos;
    Proceso proceso; // se crea objeto proceso 
    ssize_t bytesLeidos; // guarda los bytes leídos desde la pipe

    // se ocupa chrono para obtener el tiempo en el momento de ahora
    chrono::time_point<chrono::high_resolution_clock> tiempoInicio = chrono::high_resolution_clock::now();

    cout << "Se abre el pipe en modo lectura" << endl; 

    int fifo_pipe = open(fifo_path, O_RDONLY); // se abre pipe en modo lectura
    if (fifo_pipe == -1) { // si existe un error al abrir la pipe, termina
        perror("Error fifo para lectura");
        exit(EXIT_FAILURE);
    }
    cout << "Empieza la recepción de procesos..." << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    while (true) {
        bytesLeidos = read(fifo_pipe, &proceso, sizeof(Proceso));
        if (bytesLeidos <= 0) {
            break;  // salir del ciclo si no hay más datos
        }
        
        // calcular el tiempo de llegada (tiempo desde el inicio del programa en segundos)
        chrono::time_point<chrono::high_resolution_clock> tiempoActual = chrono::high_resolution_clock::now();
        // el tiempo de llegada es igual a el tiempo actual menos el tiempo en el que inicio
        int tiempoLlegada = static_cast<int>(chrono::duration_cast<chrono::seconds>(tiempoActual - tiempoInicio).count());

        cout << "Proceso recibido correctamente." << endl;
        cout << "Con ID: " << proceso.id << " llegó en " << tiempoLlegada << " segundos con un burst de " << proceso.burst << " segundos." << endl;

        colaProcesos.push(proceso); // se encola el proceso
        sleep(proceso.burst); // se simula el uso del CPU con un sleep al burst del proceso

        // cclcular el tiempo de término (tiempo en el que terminó el proceso en segundos desde el inicio)
        tiempoActual = chrono::high_resolution_clock::now();
        // tiempo de termino es el tiempo en este instante menos cuando inició
        int tiempoTermino = static_cast<int>(chrono::duration_cast<chrono::seconds>(tiempoActual - tiempoInicio).count());

        // calcular el turnaround (tiempo de término - tiempo de llegada)
        int turnaround = tiempoTermino - tiempoLlegada;

        cout << "El tiempo de término es: " << tiempoTermino << " segundos." << endl;
        cout << "Con un turnaround de: " << turnaround << " segundos." << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        colaProcesos.pop(); // se elimina el proceso de la cola tras ejecutarse
    }

    close(fifo_pipe); // cuando termina la tarea, se cierra la pipe
    cout << "Se cierra la pipe..." << endl;
    unlink(fifo_path);
    cout << "Unlinkeando pipe..." << endl;
    return 0; 
}

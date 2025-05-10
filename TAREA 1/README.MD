
...................................................... COMO EJECUTAR .......................................................................

Para ejecutar el código se deben abrir dos terminales por separado, una para central.cpp y otra para proceso.cpp.
Se debe localizar la carpeta con los archivos y crear los ejecutables, ingresando por consola:

(proceso.cpp)
g++ -o proceso proceso.cpp
(central.cpp)
g++ -o central central.cpp

Luego, ejecutar primero proceso.cpp ingresando por consola

(proceso.cpp)
./proceso

Después, ejecutar central.cpp.
(central.cpp)
./central

De esta manera el código se va a ejecutar correctamente, ejecutando proceso.cpp primero que central.cpp.

....................................................CÓMO FUNCIONA EL CÓDIGO ................................................................

El código funciona en base al algoritmo FCFS, para los códigos se define un proceso, este proceso tendrá ID, tiempo de llegada y burst.

central.cpp creará un archivo "miPipe" mediante mkfifo y se abrirá la pipe en modo lectura, además de una queue para ir guardando los procesos dentro de una cola siguiendo la metodologia del algoritmo FCS, se ocupa chrono para obtener distintos tiempos a lo largo del codigo, despues el while irá leyendo procesos desde la pipe usando read, mientra haya datos irá procesando cada tarea recibida. Se calculan los tiempos usando la funcion chrono, cada vez que un proceso es recibido correctamente se imprime su informacion y se encola y se hace un sleep para simular el uso de CPU, se calcula el tiempo de termino y el turnaround con chrono para mostrarlo por pantalla. Finalmente se elimina la cola y se cierra la pipe al terminar el código.

proceso.cpp creará un archivo "miPipe" mediante mkfiko y se abrirá la pipe en modo escritura, y se creará una seed aleatoria para ir mandando N tareas entre 3 y 6, despues, se crearan y se enviaran tareas con un for para la cantidad de tareas creadas, donde se le asignara un id y un tiempo simulado de cpu aleatoria entre 1 y 5 segundos. Se enviara la tarea a la pipe mediante write y será recibida por central.cpp, luego, se imprimirá la informacion de la tarea enviada, finalmente, se duerme el programa un tiempo entre 1 y 3s para no correr el riesgo de que el planificador no alcance a leer todas las tareas si se cierra la pipe muy rápido y se cierra la pipe.
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "struct.h"

class FileSystem {
private:
    INodo* raiz;
    INodo* actual;
    int siguienteID;

public:
    FileSystem();
    void inicializar();

    string getRutaActual();
    void listar();
    void crearDirectorio(string nombre);
    void crearArchivo(string nombre);
    void cambiarDirectorio(string nombre);
};

#endif

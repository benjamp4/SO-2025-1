#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <vector>
#include <ctime>

using namespace std;
struct INodo {
    int id; // id
    string nombre; // nombre del archivo o del directorio
    string ruta; // ruta absoluta
    bool esDirectorio; // verificiar si es un directorio
    int size; // tamaño en bytes
    string permisos; // permisos unix
    time_t created; // fecha de creación
    vector<INodo*> hijo; // hijos si es un directorio
    INodo* padre; // nodo padre (nullptr si es root)
};

#endif

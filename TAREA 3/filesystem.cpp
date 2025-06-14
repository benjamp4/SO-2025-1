#include "filesystem.h"
#include <iostream>
#include <ctime>

using namespace std;

FileSystem::FileSystem() {
    raiz = nullptr;
    actual = nullptr;
    siguienteID = 0;
}

void FileSystem::inicializar() {
    raiz = new INodo();
    raiz->id = siguienteID++;
    raiz->nombre = "/";
    raiz->ruta = "/";
    raiz->esDirectorio = true;
    raiz->size = 0;
    raiz->permisos = "rwx";
    raiz->created = time(nullptr);
    raiz->padre = nullptr;
    actual = raiz;
}

string FileSystem::getRutaActual() {
    return actual->ruta;
}

// COMANDO LS

void FileSystem::listar() {
    for (size_t i = 0; i < actual->hijo.size(); i++) {
        INodo* hijo = actual->hijo[i];
        if (hijo->esDirectorio == true) {
            cout << "[D] ";
        }
        else {
            cout << "[F] ";
        }
        cout << hijo->nombre << " (ID: " << hijo->id << ")" << endl;
    }
}

// COMANDO MKDIR

void FileSystem::crearDirectorio(string nombre) {
    for (size_t i = 0; i < actual->hijo.size(); i++) {
        INodo* hijo = actual->hijo[i];
        if (hijo->nombre == nombre && hijo->esDirectorio == true) {
            cout << "Ya existe un directorio con ese nombre." << endl;
            return;
        }
    }

    INodo* nuevo = new INodo();
    nuevo->id = siguienteID++;
    nuevo->nombre = nombre;
    if (actual->ruta == "/") {
        nuevo->ruta = "/" + nombre;
    }
    else {
        nuevo->ruta = actual->ruta + "/" + nombre;
    }
    nuevo->esDirectorio = true;
    nuevo->size = 0;
    nuevo->permisos = "rwx";
    nuevo->created = time(nullptr);
    nuevo->padre = actual;
    actual->hijo.push_back(nuevo);
    cout << "Directorio '" << nombre << "' creado." << endl;
}

// COMANDO TOUCH

void FileSystem::crearArchivo(string nombre) {
    for (size_t i = 0; i < actual->hijo.size(); i++) {
        INodo* hijo = actual->hijo[i];
        if (hijo->nombre == nombre && hijo->esDirectorio == false) {
            cout << "Ya existe un archivo con ese nombre." << endl;
            return;
        }
    }        

    INodo* nuevo = new INodo();
    nuevo->id = siguienteID++;
    nuevo->nombre = nombre;
    if (actual->ruta == "/") {
        nuevo->ruta = "/" + nombre;
    }
    else {
        nuevo->ruta = actual->ruta + "/" + nombre;
    }
    nuevo->esDirectorio = false;
    nuevo->size = 0;
    nuevo->permisos = "rw-";
    nuevo->created = time(nullptr);
    nuevo->padre = actual;
    actual->hijo.push_back(nuevo);
    cout << "Archivo '" << nombre << "' creado." << endl;
}

// COMANDO CD

void FileSystem::cambiarDirectorio(string nombre) {
    if (nombre == "..") {
        if (actual->padre != nullptr) {
            actual = actual->padre;
        }
        return;
    }

    for (size_t i = 0; i < actual->hijo.size(); i++) {
        INodo* hijo = actual->hijo[i];
        if (hijo->nombre == nombre && hijo->esDirectorio) {
            actual = hijo;
            return;
        }   
    }

    cout << "No existe el directorio '" << nombre << "'." << endl;
}

#include <iostream>
#include <sstream>
#include "filesystem.h"

using namespace std;

int main() {
    FileSystem fs;
    fs.inicializar();

    string comando;
    cout << "=== Sistema de archivos ===" << endl;

    while (true) {
        cout << fs.getRutaActual() << " > ";
        getline(cin, comando);

        if (comando == "exit") break;
        else if (comando == "ls") fs.listar();
        else if (comando.rfind("mkdir ",0) == 0) {
            string nombre = comando.substr(6); // substring, para ver lo que sigue despues de mkdir (ejemplo)
            fs.crearDirectorio(nombre);
        }
        else if (comando.rfind("touch ",0) == 0) {
            string nombre = comando.substr(6);
            fs.crearArchivo(nombre);
        
        }
        else if (comando.rfind("cd",0) == 0){
            string nombre = comando.substr(3);
            fs.cambiarDirectorio(nombre);
        }

        else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0;
}

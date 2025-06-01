#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Arista {
    string desde;
    string hasta;
    int costo;
};

int main() {
    srand(time(0)); // Inicializa la semilla para generar números aleatorios

    vector<Arista> aristas;

    // Nodo inicial: eit
    string nodo_inicial = "eit";

    // Nodo final: casa
    string nodo_final = "casa";

    // Conexión: eit -> n1 a n5
    for (int i = 1; i <= 5; ++i) {
        int costo = 5 + rand() % 16;
        Arista a;
        a.desde = nodo_inicial;
        a.hasta = "n" + to_string(i);
        a.costo = costo;
        aristas.push_back(a);
    }

    // Conexiones por niveles:
    // n1–n5 -> n6–n10 -> n11–n15 ... hasta n56–n60
    for (int i = 1; i <= 55; i += 5) {
        for (int desde = i; desde < i + 5; ++desde) {
            for (int hasta = i + 5; hasta < i + 10; ++hasta) {
                int costo = 5 + rand() % 16;
                Arista a;
                a.desde = "n" + to_string(desde);
                a.hasta = "n" + to_string(hasta);
                a.costo = costo;
                aristas.push_back(a);
            }
        }
    }

    // Último grupo: n56–n60 -> casa
    for (int i = 56; i <= 60; ++i) {
        int costo = 5 + rand() % 16;
        Arista a;
        a.desde = "n" + to_string(i);
        a.hasta = nodo_final;
        a.costo = costo;
        aristas.push_back(a);
    }

    // Mostrar resultados
    cout << "Total de nodos: 62" << endl;
    cout << "Total de aristas: " << aristas.size() << endl << endl;

    for (int i = 0; i < aristas.size(); ++i) {
        cout << aristas[i].desde << " -> " << aristas[i].hasta
             << " [costo: " << aristas[i].costo << "]" << endl;
    }

    return 0;
}
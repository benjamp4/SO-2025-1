#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>

using namespace std;

struct Arista {
    string hasta;
    int costo;
};

map<string, vector<Arista>> grafo;
mutex mtx;
int mejor_costo = INT_MAX;
int contador = 0;

void construir_dag() {
    srand(time(0));

    // eit -> n1 a n5
    for (int i = 1; i <= 5; ++i) {
        int costo = 5 + rand() % 16;
        grafo["eit"].push_back({"n" + to_string(i), costo});
    }

    // n1–n5 -> n6–n10 -> ... -> n56–n60
    for (int i = 1; i <= 55; i += 5) {
        for (int desde = i; desde < i + 5; ++desde) {
            for (int hasta = i + 5; hasta < i + 10; ++hasta) {
                int costo = 5 + rand() % 16;
                grafo["n" + to_string(desde)].push_back({"n" + to_string(hasta), costo});
            }
        }
    }

    // n56–n60 -> casa
    for (int i = 56; i <= 60; ++i) {
        int costo = 5 + rand() % 16;
        grafo["n" + to_string(i)].push_back({"casa", costo});
    }
}

void recorrer(string inicio, string fin, chrono::steady_clock::time_point tiempo_limite) {
    while (chrono::steady_clock::now() < tiempo_limite) {
        string actual = inicio;
        int costo_total = 0;

        while (actual != fin) {
            if (grafo[actual].empty()) break;

            int index = rand() % grafo[actual].size();
            Arista siguiente = grafo[actual][index];
            costo_total += siguiente.costo;
            actual = siguiente.hasta;
        }

        if (actual == fin) {
            lock_guard<mutex> lock(mtx);
            if (costo_total < mejor_costo) {
                mejor_costo = costo_total;
                contador++;
                cout << contador <<". [Nuevo costo encontrado]: " << mejor_costo << endl;
            }
        }
    }
}

int main() {
    construir_dag();

    int opcion, K = 0;

    cout << "=== Simulador de Recorridos en el DAG ===" << endl;
    cout << "Seleccione la cantidad de threads a usar:" << endl;
    cout << "1. 1 thread" << endl;
    cout << "2. 10 threads" << endl;
    cout << "3. 20 threads" << endl;
    cout << "4. 50 threads" << endl;
    cout << "5. 100 threads" << endl << endl;
    cout << "Opción: "<< endl;
    cin >> opcion;

    switch (opcion) {
        case 1: K = 1; break;
        case 2: K = 10; break;
        case 3: K = 20; break;
        case 4: K = 50; break;
        case 5: K = 100; break;
        default:
            cout << "Opción inválida. Se usará 10 threads por defecto." << endl;
            K = 10;
    }

    cout << "Iniciando " << K << " hilos por 60 segundos..." << endl;

    vector<thread> hilos;
    chrono::time_point<chrono::steady_clock> fin = chrono::steady_clock::now() + chrono::seconds(60);

    for (int i = 0; i < K; ++i) {
        hilos.push_back(thread(recorrer, "eit", "casa", fin));
    }

    for (int i = 0; i < K; ++i) {
        hilos[i].join();
    }

    cout <<"Mejor ruta encontrada: " << mejor_costo << endl;
    return 0;
}

// g++ -std=c++11 -pthread -o item2 item2.cpp
// ./item2



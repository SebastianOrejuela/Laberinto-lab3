#include "laberinto.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Implementación del constructor
Laberinto::Laberinto(int f, int c) : filas(f), columnas(c) {
    srand(time(0));
    inicializarMatriz();
}

// Implementación de método privado
void Laberinto::inicializarMatriz() {
    mapa.resize(filas, vector<int>(columnas));
    vector<vector<int>> labPersonalizado = {
        {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
    };
    mapa = labPersonalizado;
   /* for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            mapa[i][j] = rand() % 2;
        }
    }
    mapa[filas-1][columnas-1] = 1;
 */

}

// Implementación de métodos públicos
void Laberinto::mostrar() const {
    cout << "\nLaberinto " << filas << "x" << columnas << ":\n";
    for (const auto& fila : mapa) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

const vector<vector<int>>& Laberinto::obtenerMatriz() const {
    return mapa;
}

int Laberinto::obtenerFilas() const {
    return filas;
}

int Laberinto::obtenerColumnas() const {
    return columnas;
}
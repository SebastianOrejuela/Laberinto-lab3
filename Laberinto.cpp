/*    Clase: Laberinto

Descripción:
    Esta clase representa un laberinto en forma de matriz bidimensional.
    Cada celda puede ser un camino (1) o un obstáculo/precipicio (0).
    Se puede personalizar el tamaño del laberinto, y hay flexibilidad para
    utilizar un diseño aleatorio o uno personalizado.

    En esta versión, se ha elegido un diseño fijo para asegurar que exista
    al menos un camino viable desde cualquier punto hasta la salida, lo cual
    es útil para pruebas de algoritmos de búsqueda y depuración.

    Funcionalidades:
    - mostrar(): Imprime la matriz del laberinto en consola.
    - obtenerMatriz(): Retorna una referencia constante a la matriz.
    - obtenerFilas() / obtenerColumnas(): Devuelven el tamaño del laberinto.

    Detalles técnicos:
    - El laberinto está representado como un `vector<vector<int>>`.
    - Las posiciones con valor 1 representan caminos; las de valor 0, precipioes.
    - El constructor permite definir el tamaño del laberinto.
    - La matriz se inicializa con un patrón personalizado por defecto.
    */
#include "laberinto.h"
#include <iostream>
#include <cstdlib> //Permite generar números aleatorios con srand
#include <ctime>
using namespace std;

// Se diseña así para si en algún momento se quiere ampliar el tamaño del labernto
Laberinto::Laberinto(int f, int c) : filas(f), columnas(c) {
    srand(time(0));
    inicializarMatriz();
}

void Laberinto::inicializarMatriz() {
    mapa.resize(filas, vector<int>(columnas));
    vector<vector<int>> labPersonalizado = { //En este caso decidí crear mi propio laberinto porque cuando lo generaba aleatorio era muy duro que hubieran caminos factibles
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
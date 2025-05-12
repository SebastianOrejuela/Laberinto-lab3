//
// Created by Sebastián Orejuela on 11/05/2025.
//

#ifndef LABERINTO_H
#define LABERINTO_H

#include <vector>
using namespace std;

class Laberinto {
private:
    vector<vector<int>> mapa;
    int filas;
    int columnas;

    void inicializarMatriz();  // Solo declaración

public:
    Laberinto(int f = 10, int c = 10);  // Constructor

    void mostrar() const;  // Declaración
    const vector<vector<int>>& obtenerMatriz() const;  // Declaración
    int obtenerFilas() const;  // Declaración
    int obtenerColumnas() const;  // Declaración
};

#endif // LABERINTO_H
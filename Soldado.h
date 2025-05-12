//
// Created by Sebastián Orejuela on 10/05/2025.
//
#ifndef SOLDADO_H
#define SOLDADO_H

#include "laberinto.h"
#include <vector>
#include <stack>

using namespace std;

class Soldado {
private:
    int filaActual;
    int columnaActual;
    Laberinto* laberinto;
    vector<vector<bool>> visitadas;
    stack<pair<int, int>> camino;

    bool mover(int df, int dc);
    bool explorarAdyacentes();
    void retroceder();

public:
    Soldado(Laberinto* lab);
    void encontrarSalida();
    int getFila() const;
    int getColumna() const;
};

#endif // SOLDADO_H
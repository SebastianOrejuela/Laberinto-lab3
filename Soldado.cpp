//
// Created by Sebastián Orejuela on 10/05/2025.
//
#include "soldado.h"
#include <iostream>

Soldado::Soldado(Laberinto* lab) : laberinto(lab) {
    srand(time(0));
    visitadas.resize(lab->obtenerFilas(), vector<bool>(lab->obtenerColumnas(), false));

    // Posición inicial aleatoria válida
    do {
        filaActual = rand() % laberinto->obtenerFilas();
        columnaActual = rand() % laberinto->obtenerColumnas();
    } while(!laberinto->obtenerMatriz()[filaActual][columnaActual] ||
           (filaActual == laberinto->obtenerFilas()-1 &&
            columnaActual == laberinto->obtenerColumnas()-1));

    visitadas[filaActual][columnaActual] = true;
    camino.push({filaActual, columnaActual});
}

bool Soldado::mover(int df, int dc) {
    int nuevaFila = filaActual + df;
    int nuevaCol = columnaActual + dc;

    // Verificar límites, camino válido y no visitado
    if(nuevaFila >= 0 && nuevaFila < laberinto->obtenerFilas() &&
       nuevaCol >= 0 && nuevaCol < laberinto->obtenerColumnas() &&
       laberinto->obtenerMatriz()[nuevaFila][nuevaCol] == 1 &&
       !visitadas[nuevaFila][nuevaCol]) {

        filaActual = nuevaFila;
        columnaActual = nuevaCol;
        visitadas[filaActual][columnaActual] = true;
        camino.push({filaActual, columnaActual});

        // Mostrar movimiento
        if(df == 1) cout << "↓ Abajo -> ";
        else if(df == -1) cout << "↑ Arriba -> ";
        else if(dc == 1) cout << "→ Derecha -> ";
        else cout << "← Izquierda -> ";

        cout << "[" << filaActual << "," << columnaActual << "]\n";
        return true;
    }
    return false;
}

bool Soldado::explorarAdyacentes() {
    // Intenta moverse en las 4 direcciones
    if(mover(1, 0)) return true;   // Abajo
    if(mover(0, 1)) return true;   // Derecha
    if(mover(-1, 0)) return true;  // Arriba
    if(mover(0, -1)) return true;  // Izquierda
    return false;
}

void Soldado::retroceder() {
    if(camino.size() > 1) {
        camino.pop(); // Eliminar posición actual
        auto anterior = camino.top();
        filaActual = anterior.first;
        columnaActual = anterior.second;
        cout << "↺ Retroceso -> [" << filaActual << "," << columnaActual << "]\n";
    }
}

void Soldado::encontrarSalida() {
    const int MAX_MOVIMIENTOS = 1000;
    int movimientos = 0;

    while(movimientos < MAX_MOVIMIENTOS) {
        // Verificar si llegó a la salida
        if(filaActual == laberinto->obtenerFilas()-1 &&
           columnaActual == laberinto->obtenerColumnas()-1) {
            cout << "¡Llegó a la salida!\n";
            return;
        }

        // Intentar moverse a celdas no visitadas
        if(explorarAdyacentes()) {
            movimientos++;
            continue;
        }

        // Si no puede moverse, retroceder
        if(camino.size() > 1) {
            retroceder();
            movimientos++;
            continue;
        }

        // Si no puede moverse ni retroceder
        cout << "No hay solución desde [" << filaActual << "," << columnaActual << "]\n";
        return;
    }

    cout << "Límite de movimientos alcanzado\n";
}

int Soldado::getFila() const {
    return filaActual;
}

int Soldado::getColumna() const {
    return columnaActual;
}
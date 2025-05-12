#include "laberinto.h"
#include "soldado.h"
#include <iostream>

int main() {
    // Crear laberinto 10x10
    Laberinto laberinto(10, 10);
    laberinto.mostrar();

    // Crear soldado en el laberinto
    Soldado soldado(&laberinto);
    std::cout << "\nPosición inicial del soldado: ("
              << soldado.getFila() << "," << soldado.getColumna() << ")\n";

    // Intentar encontrar la salida
    std::cout << "\nBuscando salida...\n";
    soldado.encontrarSalida();

    return 0;
}
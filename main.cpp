/* * Archivo: main.cpp
* Descripción: Este programa crea un laberinto de 10x10 y posiciona un soldado en una celda aleatoria
*              que no sea la salida. El soldado explora el laberinto hasta encontrar una ruta a la salida
*              (esquina inferior derecha), retrocediendo si se encuentra sin salida.
*
* Este archivo incluye:
*  - "laberinto.h": Define y genera la estructura del laberinto.
*  - "soldado.h": Contiene la lógica del personaje que recorre el laberinto.
*  Autores:
*  Sebastian Orejuela 202439875
*  Jairo Tegue 2416227
*  Andrés Felipe Muñoz Moreno 2438908
*  Juan Sebastian Tapia
*  NOTA: En lugar de clase Avatar decidimos llamarle Soldado ya que es el nombre que tiene en el juego
*  */
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

    // Intenta encontar la salida
    std::cout << "\nBuscando salida...\n";
    soldado.encontrarSalida();

    return 0;
}
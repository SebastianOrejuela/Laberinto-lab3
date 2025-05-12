//
// Created by Sebastián Orejuela on 10/05/2025.
//
/*    Descripción:
Esta clase representa a un soldado que se mueve dentro de un laberinto.
Su propósito es encontrar una salida desde una posición inicial aleatoria
(que no sea la meta), explorando las celdas transitables del laberinto.

Utiliza una pila (stack) para registrar el camino recorrido, permitiendo
retroceder cuando se encuentra sin opciones de avance. Lleva también una
matriz de booleanos para marcar las posiciones ya visitadas y evitar ciclos.

Métodos clave:
- encontrarSalida(): Ejecuta la búsqueda hasta hallar la salida o rendirse.
- mover(): Intenta mover al soldado en una dirección dada si es válido.
- retroceder(): Revierte el último paso si no hay movimientos posibles.
- explorarAdyacentes(): Prueba moverse a las casillas vecinas en orden fijo.
- getFila(), getColumna(): Devuelven la posición actual del soldado.

Requiere:
- Un puntero a un objeto Laberinto ya inicializado.
- Que el laberinto proporcione acceso a su matriz, filas y columnas.

*/
#include "soldado.h"
#include <iostream>

Soldado::Soldado(Laberinto* lab) : laberinto(lab) {
    srand(time(0)); // Esto es para que cada vez el soldadito aparezca en un lugar diferente

    // Inicializo la matriz visitadas del mismo tamaño que el laberinto, en falso.
    // Es para saber en qué casillas ya he estado y no repetirlassi no es full necesario
    visitadas.resize(lab->obtenerFilas(), vector<bool>(lab->obtenerColumnas(), false));

    // Aquí pongo al soldado en un lugar random para que empiece,
    // teniendo en cuenta que no puede estar en un 0 porque es precipicio ni en la casilla de ganar.
    do {
        filaActual = rand() % laberinto->obtenerFilas();
        columnaActual = rand() % laberinto->obtenerColumnas();
    } while(!laberinto->obtenerMatriz()[filaActual][columnaActual] || // Si es un precipio 0, no sirve.
           (filaActual == laberinto->obtenerFilas()-1 &&              // Y tampoco puede empezar ya en la meta.
            columnaActual == laberinto->obtenerColumnas()-1));

    // Aqui voy poniendo que la  casilla ya la visité
    visitadas[filaActual][columnaActual] = true;

    // Guardo la posición inicial en el "camino", que es para saber mi última posición y así retroceder si algo
    camino.push({filaActual, columnaActual});
}

bool Soldado::mover(int df, int dc) {
    // df (direcciónfila) y dc (doreccioncolumna) son los desplazamientos en fila y columna
    int nuevaFila = filaActual + df;
    int nuevaCol = columnaActual + dc;

    // Aquí reviso si esa nueva posición está dentro del laberinto, si no es un precipicio 0
    // y si no la he visitado antes para no caer en bucles y bucles terriblees
    if(nuevaFila >= 0 && nuevaFila < laberinto->obtenerFilas() &&
       nuevaCol >= 0 && nuevaCol < laberinto->obtenerColumnas() &&
       laberinto->obtenerMatriz()[nuevaFila][nuevaCol] == 1 &&
       !visitadas[nuevaFila][nuevaCol]) {

        // Actualizo la posición
        filaActual = nuevaFila;
        columnaActual = nuevaCol;

        // Marco como visitada cada lugar al que voy yendo
        visitadas[filaActual][columnaActual] = true;

        // Guardo esta nueva posición en el camino, lo mismo que hice para la posición inicial solo que esta ves para cada movimineto
        camino.push({filaActual, columnaActual});

        // Imprimo la dirección en la que me moví, esto es como parau qe uno pueda ver que está haciendo el muñequito
        if(df == 1) cout << "Abajo -> ";
        else if(df == -1) cout << "Arriba -> ";
        else if(dc == 1) cout << "Derecha -> ";
        else cout << "Izquierda -> ";

        // Se complementa con el de arriba, solo para que salga el nuevo luegar en el que estoy
        cout << "[" << filaActual << "," << columnaActual << "]\n";

        return true;
    }

    // Si no puedo moverme a esa celda, devuelvo falso.
    return false;
}

bool Soldado::explorarAdyacentes() {
    // Aquí intento moverme en las 4 direcciones abajo, derecha, arriba e izquierda, primero abajo y derecha ya que por allá se encuentr la salida
    if(mover(1, 0)) return true;   // Abajo
    if(mover(0, 1)) return true;   // Derecha
    if(mover(-1, 0)) return true;  // Arriba
    if(mover(0, -1)) return true;  // Izquierda

    // Si no me puedo mover en ninguna dirección, devuelvo false, esto para decir que es un punto inválido sin caminos
    return false;
}

void Soldado::retroceder() {
    // Si hay más de una posición en el stack (o sea, no estoy en el punto de inicio es para saber que por ahí ya estuve y chao
    if(camino.size() > 1) {
        camino.pop(); // Quito la posición actualporque estoy retrocediendo
        auto anterior = camino.top(); // La anterior se convierte en mi nueva posición
        filaActual = anterior.first;
        columnaActual = anterior.second;

        // Imprimo que estoy retrocediendo, al igual que con derecha, abajo etc,.
        cout << "↺ Retroceso -> [" << filaActual << "," << columnaActual << "]\n";
    }
}

void Soldado::encontrarSalida() {
    const int MAX_MOVIMIENTOS = 1000; // Por si acaso se queda atrapado en un bucle para que no intente infinitas veces, sino que si en 1000 no sale ya no salió
    int movimientos = 0;

    while(movimientos < MAX_MOVIMIENTOS) {
        // Reviso si estoy en la casilla de salida, o sea en cada movimiento reviso si llegué
        if(filaActual == laberinto->obtenerFilas()-1 &&
           columnaActual == laberinto->obtenerColumnas()-1) {
            cout << "¡Llegó a la salida!\n";
            return;
        }

        // Intento moverme a alguna casilla válida no visitada.
        if(explorarAdyacentes()) {
            movimientos++; // Solo cuento el movimiento si logré moverme.
            continue;
        }

        // Si no me pude mover, entonces retrocedo.
        if(camino.size() > 1) {
            retroceder();
            movimientos++; // También cuento el retroceso como movimiento.
            continue;
        }

        // Si no puedo moverme ni retroceder, entonces no hay solución desde donde empecé.
        cout << "No hay solución desde [" << filaActual << "," << columnaActual << "]\n";
        return;
    }

    // Si llegué al límite de movimientos sin encontrar salida.
    cout << "Límite de movimientos alcanzado\n";
}

// Métodos para obtener en qué fila y columna está el soldado (por si se necesita desde fuera main o algo así
int Soldado::getFila() const {
    return filaActual;
}

int Soldado::getColumna() const {
    return columnaActual;
}

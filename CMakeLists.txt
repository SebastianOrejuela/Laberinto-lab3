cmake_minimum_required(VERSION 3.30)
project(Laberinto)

set(CMAKE_CXX_STANDARD 20)

# Incluir todos los archivos fuente necesarios
add_executable(Laberinto
        main.cpp
        laberinto.cpp
        soldado.cpp
)

# Opcional: habilitar advertencias adicionales
target_compile_options(Laberinto PRIVATE -Wall -Wextra -pedantic)
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "Structs.h"
using namespace std;

class Tablero {
public:
    Celda board[FILAS][COLUMNAS];
    vector<Ruta> rutas;
    map<string, Ciudad> ciudades;

    Tablero(); // Constructor

    void inicializarTableroBase(); // Inicializa el tablero con celdas vacías y letras de ciudades
    void dibujarRutasEnTablero();  // Dibuja las rutas predefinidas en el tablero
    void inicializarCiudadesYRutas(); // Inicializa las ciudades y rutas del juego
    void actualizarGraficoRutaReclamada(int rutaId); // Cambia el color de una ruta reclamada a blanco
    void imprimirCelda(const Celda& celda) const; // Imprime una sola celda del tablero
    void display() const; // Muestra el tablero completo
    void mostrarRutasDisponibles() const; // Muestra las rutas que aún no han sido reclamadas
    Ruta* getRutaPorId(int id); // Obtiene un puntero a una ruta por su ID
};

#endif


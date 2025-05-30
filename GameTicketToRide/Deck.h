#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <stdexcept>
#include "Structs.h"
using namespace std;

class Mazo {
public:
    vector<CartaTren> cartas;
    vector<CartaTren> descarte;
    mt19937 rng; // Generador de números aleatorios para barajar

    Mazo();

    void inicializar(); // Inicializa el mazo con todas las cartas de tren
    void barajar(); // Baraja las cartas en el mazo principal
    CartaTren robarCarta(); // Roba una carta del mazo principal
    void agregarADescarte(const CartaTren& carta); // Agrega una carta al mazo de descarte
    bool tieneCartasDisponibles() const; // Verifica si hay cartas disponibles en el mazo principal o de descarte
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Structs.h"
#include "Deck.h"
using namespace std;

class Jugador {
public:
    int id;
    string nombre;
    vector<CartaTren> mano;
    int vagonesRestantes;
    int puntaje = 0;

    Jugador(int _id, string _nombre);

    void tomarCarta(const CartaTren& carta); // Agrega una carta a la mano del jugador
    void mostrarMano() const; // Muestra la mano del jugador, vagones y puntos
    int contarCartas(const string& color) const; // Cuenta las cartas de un color específico en la mano
    bool tieneCartasSuficientes(const string& colorRuta, int cantidad); // Verifica si tiene suficientes cartas para una ruta
    void jugarCartas(const string& colorRuta, int cantidad, Mazo& mazoDescarte); // Juega cartas para reclamar una ruta
};

#endif
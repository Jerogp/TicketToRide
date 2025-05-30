#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <limits>    
#include <iostream>  
#include <algorithm> 

#include "Board.h"
#include "Deck.h"
#include "Player.h"
#include "Constants.h"
using namespace std;

class JuegoDeTrenes {
public:
    Tablero tablero; 
    vector<Jugador> jugadores;
    Mazo mazoPrincipal;
    int jugadorActualIdx = 0;
    bool juegoTerminado = false;
    int rondasFinales = 0;

    static const int NUM_CARTAS_VISIBLES = 4;
    vector<CartaTren> cartasVisibles;

    explicit JuegoDeTrenes(int numJugadores);
    
    void iniciarJuego(); // Inicializa el juego (mazo, cartas visibles, manos iniciales)
    void rellenarCartasVisibles(int indiceSlot); // Rellena un espacio de carta visible
    void accionRobarCartas(Jugador& jugador); // Lógica para que un jugador robe cartas
    void jugar(); // Bucle principal del juego
    void turno(); // Lógica para un turno de jugador
    bool accionReclamarRuta(Jugador& jugador); // Lógica para que un jugador reclame una ruta
    void determinarGanador(); // Determina y anuncia al ganador del juego
};

#endif
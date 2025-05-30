#include <iostream>
#include <limits>
#include "Game.h"
#include "Constants.h"
using namespace std;

int main() {
    int numJugadores;
    do {
        cout << "Ingrese el número de jugadores (2-4): ";
        cin >> numJugadores;
        if (cin.fail() || numJugadores < 2 || numJugadores > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Número inválido. Debe ser entre 2 y 4.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            break;
        }
    } while (true);

    cout << "\n¡Bienvenido al juego de trenes!\n";
    JuegoDeTrenes juego(numJugadores); 
    juego.jugar();

    return 0;
}
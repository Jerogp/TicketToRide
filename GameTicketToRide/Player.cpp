#include "Player.h"
using namespace std;

Jugador::Jugador(int _id, string _nombre) {
    id = _id;
    nombre = move(_nombre);
    vagonesRestantes = 18;
}

// Agrega una carta a la mano del jugador
void Jugador::tomarCarta(const CartaTren& carta) {
    mano.push_back(carta);
}

// Muestra la mano del jugador, vagones restantes y puntuación
void Jugador::mostrarMano() const {
    cout << "Mano de " << nombre << " (Vagones: " << vagonesRestantes << ", Puntos: " << puntaje << "):\n";

    if (mano.empty()) {
        cout << "(Vacía)\n";
        return;
    }

    string lineaContenido;
    for (const auto& carta : mano) {
        lineaContenido += carta.obtenerVisualContenido() + " ";
    }
    cout << lineaContenido << endl;
}

// Cuenta el número de cartas de un color específico en la mano del jugador
int Jugador::contarCartas(const string& color) const {
    return count_if(mano.begin(), mano.end(), [&](const CartaTren& carta){
        return carta.color == color;
    });
}

// Verifica si el jugador tiene suficientes cartas de un color específico para reclamar una ruta
bool Jugador::tieneCartasSuficientes(const string& colorRuta, int cantidad) {
    return contarCartas(colorRuta) >= cantidad;
}

// Juega cartas para reclamar una ruta, moviéndolas al mazo de descarte
void Jugador::jugarCartas(const string& colorRuta, int cantidad, Mazo& mazoDescarte) {
    int cartasParaDescartar = cantidad;
    auto it = mano.begin();
    while (it != mano.end() && cartasParaDescartar > 0) {
        if (it->color == colorRuta) {
            mazoDescarte.agregarADescarte(*it); // Mueve la carta al descarte
            it = mano.erase(it); // Elimina la carta de la mano
            cartasParaDescartar--;
        } else {
            ++it; // Avanza al siguiente elemento si no coincide el color
        }
    }
}
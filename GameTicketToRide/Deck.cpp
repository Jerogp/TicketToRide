#include "Deck.h"
#include <iostream>
using namespace std;

Mazo::Mazo() {
    random_device rd;
    rng = mt19937(rd());
}

void Mazo::inicializar() {
    cartas.clear();
    descarte.clear();
    const vector<string> colores = {"Rojo", "Azul", "Verde", "Morado", "Cafe", "Naranja"};
    for (const auto& color : colores) {
        for (int i = 0; i < 12; ++i) cartas.push_back(CartaTren(color));
    }
    barajar();
}

void Mazo::barajar() {
    shuffle(cartas.begin(), cartas.end(), rng);
}

// Roba una carta del mazo principal, barajando el descarte si es necesario
CartaTren Mazo::robarCarta() {
    if (cartas.empty()) {
        if (descarte.empty()) throw runtime_error("Mazo y descarte vacios!"); // No hay cartas disponibles
        cout << "¡Barajando el mazo de descarte para reponer el mazo principal!\n";
        cartas = descarte; // Mueve las cartas del descarte al mazo principal
        descarte.clear(); // Limpia el descarte
        barajar(); // Baraja el nuevo mazo principal
        if (cartas.empty()) throw runtime_error("Mazo y descarte vacios despues de rebarajar!"); // Si aún está vacío, error
    }
    CartaTren carta = cartas.back(); // Toma la última carta
    cartas.pop_back(); // La remueve del mazo
    return carta;
}

// Agrega una carta al mazo de descarte
void Mazo::agregarADescarte(const CartaTren& carta) {
    descarte.push_back(carta);
}

// Verifica si hay cartas disponibles en el mazo principal o de descarte
bool Mazo::tieneCartasDisponibles() const {
    return !cartas.empty() || !descarte.empty();
}
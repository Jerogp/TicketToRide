#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <utility>

#include "Constants.h"
using namespace std;

struct Celda {
    string color;
    char letra;
};

struct CartaTren {
    string color;
    CartaTren(string c = "") : color(move(c)) {}

    // Obtiene la representación visual del contenido de la carta
    string obtenerVisualContenido() const {
        if (color.empty()) return "    ";

        string colorAnsi = BG_WHITE;
        if (COLORES_ANSI.count(this->color)) {
            colorAnsi = COLORES_ANSI.at(this->color);
        }
        return colorAnsi + "    " + RESET;
    }

    void mostrar() const {
        cout << obtenerVisualContenido();
    }
};

struct Ciudad {
    string nombre;
    Ciudad(string n = "") : nombre(move(n)) {}
};

struct Ruta {
    int id;
    string ciudad1, ciudad2;
    string color;
    int longitud;
    int puntos;
    int propietarioId = -1; // -1 indica que no ha sido reclamada

    Ruta(int _id, string c1, string c2, string col, int lon)
        : id(_id), ciudad1(move(c1)), ciudad2(move(c2)), color(move(col)), longitud(lon) {
        // Asigna puntos basados en la longitud de la ruta
        if (lon == 2) puntos = 1;
        else if (lon == 3) puntos = 2;
        else if (lon == 4) puntos = 4;
        else if (lon == 5) puntos = 6;
        else if (lon == 6) puntos = 9;
        else puntos = 0;
    }

    // Muestra los detalles de la ruta
    void mostrar() const {
        cout << setw(2) << id << ". " << left << setw(8) << (ciudad1 + "-" + ciudad2)
                     << " | " << "Longitud: " << longitud;
        if (COLORES_ANSI.count(color)) {
            cout << " | Color: " << COLORES_ANSI.at(color) << " " << setw(10) << left << color << RESET;
        } else {
            cout << " | Color: " << setw(10) << left << color;
        }
        if (propietarioId != -1) {
            cout << " (Reclamada por Jugador " << propietarioId + 1 << ")";
        }
        cout << endl;
    }
};

#endif
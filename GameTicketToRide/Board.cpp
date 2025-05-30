#include "Board.h"
#include <iostream>
#include <iomanip>
using namespace std;

Tablero::Tablero() {
    inicializarTableroBase();
    inicializarCiudadesYRutas();
    dibujarRutasEnTablero();
}

// Inicializa el tablero base con celdas vacías y letras de ciudades
void Tablero::inicializarTableroBase() {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            board[i][j] = {BG_WHITE, ' '};
        }
    }
    // Asigna las letras de las ciudades en sus posiciones iniciales
    board[8][1] = {BG_WHITE, 'A'}; board[5][3] = {BG_WHITE, 'B'}; board[14][3] = {BG_WHITE, 'C'};
    board[1][4] = {BG_WHITE, 'D'}; board[4][6] = {BG_WHITE, 'E'}; board[8][6] = {BG_WHITE, 'F'};
    board[12][6] = {BG_WHITE, 'G'}; board[8][9] = {BG_WHITE, 'H'}; board[5][10] = {BG_WHITE, 'I'};
    board[2][11] = {BG_WHITE, 'J'}; board[8][12] = {BG_WHITE, 'K'}; board[12][12] = {BG_WHITE, 'L'};
    board[14][13] = {BG_WHITE, 'M'}; board[2][14] = {BG_WHITE, 'N'}; board[4][16] = {BG_WHITE, 'O'};
    board[8][16] = {BG_WHITE, 'P'}; board[12][16] = {BG_WHITE, 'Q'}; board[6][19] = {BG_WHITE, 'R'};
    board[10][19] = {BG_WHITE, 'S'};
}

// Dibuja las rutas en el tablero con sus respectivos colores
void Tablero::dibujarRutasEnTablero() {
    // Definición de las rutas por coordenadas y color
    for (int i = 5; i <= 7; ++i) board[i][1].color = BG_RED; board[5][2].color = BG_RED;
    for (int j = 2; j <= 5; ++j) board[8][j].color = BG_BLUE;
    for (int i = 5; i <= 7; ++i) board[i][6].color = BG_GREEN;
    for (int i = 1; i <= 3; ++i) board[i][6].color = BG_MARRON; board[1][5].color = BG_MARRON;
    for (int i = 9; i <= 11; ++i) board[i][6].color = BG_NARANJA;
    for (int j = 3; j <= 5; ++j) board[12][j].color = BG_MARRON; board[13][3].color = BG_MARRON;
    for (int j = 7; j <= 8; ++j) board[8][j].color = BG_NARANJA;
    for (int i = 9; i <= 12; ++i) board[i][9].color = BG_RED; for (int j = 10; j <= 11; ++j) board[12][j].color = BG_RED;
    for (int j = 10; j <= 11; ++j) board[8][j].color = BG_BLUE;
    for (int i = 9; i <= 11; ++i) board[i][12].color = BG_NARANJA;
    for (int j = 13; j <= 15; ++j) board[8][j].color = BG_GREEN;
    for (int i = 5; i <= 7; ++i) board[i][16].color = BG_NARANJA;
    board[2][16].color = BG_GREEN; board[3][16].color = BG_GREEN; board[2][15].color = BG_GREEN;
    for (int j = 12; j <= 13; ++j) board[2][j].color = BG_RED;
    for (int j = 17; j <= 19; ++j) board[4][j].color = BG_PURPLE; board[5][19].color = BG_PURPLE;
    for (int i = 9; i <= 11; ++i) board[i][16].color = BG_GREEN;
    for (int j = 14; j <= 16; ++j) board[14][j].color = BG_PURPLE; board[13][16].color = BG_PURPLE;
    for (int j = 17; j <= 19; ++j) board[12][j].color = BG_MARRON; board[11][19].color = BG_MARRON;
    for (int j = 10; j <= 12; ++j) board[6][j].color = BG_PURPLE; board[7][12].color = BG_PURPLE;
    for (int j = 10; j <= 15; ++j) board[4][j].color = BG_BLUE;
}

// Inicializa las ciudades y rutas del juego
void Tablero::inicializarCiudadesYRutas() {
    ciudades.emplace("A", Ciudad("A")); ciudades.emplace("B", Ciudad("B"));
    // Añade las rutas al vector de rutas
    rutas.emplace_back(1, "A", "B", "Rojo", 4); rutas.emplace_back(2, "A", "F", "Azul", 4);
    rutas.emplace_back(3, "F", "E", "Verde", 3); rutas.emplace_back(4, "E", "D", "Cafe", 4);
    rutas.emplace_back(5, "F", "G", "Naranja", 3); rutas.emplace_back(6, "G", "C", "Cafe", 3);
    rutas.emplace_back(7, "F", "H", "Naranja", 2); rutas.emplace_back(8, "H", "L", "Rojo", 6);
    rutas.emplace_back(9, "H", "K", "Azul", 2); rutas.emplace_back(10, "K", "L", "Naranja", 3);
    rutas.emplace_back(11, "K", "P", "Verde", 3); rutas.emplace_back(12, "P", "O", "Naranja", 3);
    rutas.emplace_back(13, "O", "N", "Verde", 3); rutas.emplace_back(14, "N", "J", "Rojo", 2);
    rutas.emplace_back(15, "O", "R", "Morado", 3); rutas.emplace_back(16, "P", "Q", "Verde", 3);
    rutas.emplace_back(17, "Q", "M", "Morado", 3); rutas.emplace_back(18, "Q", "S", "Cafe", 3);
    rutas.emplace_back(19, "I", "K", "Morado", 3); rutas.emplace_back(20, "I", "O", "Azul", 6);
}

// Actualiza la representación gráfica de una ruta reclamada a blanco
void Tablero::actualizarGraficoRutaReclamada(int rutaId) {
    // Cambia el color de las celdas de la ruta a blanco
    switch (rutaId) {
        case 1: for (int i = 5; i <= 7; ++i) board[i][1].color = BG_WHITE; board[5][2].color = BG_WHITE; break;
        case 2: for (int j = 2; j <= 5; ++j) board[8][j].color = BG_WHITE; break;
        case 3: for (int i = 5; i <= 7; ++i) board[i][6].color = BG_WHITE; break;
        case 4: for (int i = 1; i <= 3; ++i) board[i][6].color = BG_WHITE; board[1][5].color = BG_WHITE; break;
        case 5: for (int i = 9; i <= 11; ++i) board[i][6].color = BG_WHITE; break;
        case 6: for (int j = 3; j <= 5; ++j) board[12][j].color = BG_WHITE; board[13][3].color = BG_WHITE; break;
        case 7: for (int j = 7; j <= 8; ++j) board[8][j].color = BG_WHITE; break;
        case 8: for (int i = 9; i <= 12; ++i) board[i][9].color = BG_WHITE; for (int j = 10; j <= 11; ++j) board[12][j].color = BG_WHITE; break;
        case 9: for (int j = 10; j <= 11; ++j) board[8][j].color = BG_WHITE; break;
        case 10: for (int i = 9; i <= 11; ++i) board[i][12].color = BG_WHITE; break;
        case 11: for (int j = 13; j <= 15; ++j) board[8][j].color = BG_WHITE; break;
        case 12: for (int i = 5; i <= 7; ++i) board[i][16].color = BG_WHITE; break;
        case 13: board[2][16].color = BG_WHITE; board[3][16].color = BG_WHITE; board[2][15].color = BG_WHITE; break;
        case 14: for (int j = 12; j <= 13; ++j) board[2][j].color = BG_WHITE; break;
        case 15: for (int j = 17; j <= 19; ++j) board[4][j].color = BG_WHITE; board[5][19].color = BG_WHITE; break;
        case 16: for (int i = 9; i <= 11; ++i) board[i][16].color = BG_WHITE; break;
        case 17: for (int j = 14; j <= 16; ++j) board[14][j].color = BG_WHITE; board[13][16].color = BG_WHITE; break;
        case 18: for (int j = 17; j <= 19; ++j) board[12][j].color = BG_MARRON; board[11][19].color = BG_MARRON; break;
        case 19: for (int j = 10; j <= 12; ++j) board[6][j].color = BG_PURPLE; board[7][12].color = BG_PURPLE; break;
        case 20: for (int j = 10; j <= 15; ++j) board[4][j].color = BG_BLUE; break;
        default: break;
    }
}

// Imprime una sola celda del tablero
void Tablero::imprimirCelda(const Celda& celda) const {
    cout << celda.color;
    if (celda.letra != ' ') {
        cout << TEXT_BLACK << TEXT_BOLD << " " << celda.letra << " ";
    } else {
        cout << "   ";
    }
    cout << RESET;
}

// Muestra el tablero completo
void Tablero::display() const {
    cout << "\n--- MAPA DEL TABLERO ---\n";
    cout << "    "; // Espacio para la columna de números de fila
    for (int j = 1; j < COLUMNAS; ++j) {
        cout << setw(3) << j; // Números de columna
    }
    cout << "\n";

    for (int i = 1; i < FILAS; ++i) {
        cout << setw(3) << i << " "; // Números de fila
        for (int j = 1; j < COLUMNAS; ++j) {
            imprimirCelda(board[i][j]); // Imprime cada celda
        }
        cout << RESET << endl;
    }
}

// Muestra todas las rutas disponibles para reclamar
void Tablero::mostrarRutasDisponibles() const {
    cout << "--- RUTAS DISPONIBLES ---\n";
    bool hayDisponibles = false;
    for (const auto& ruta : rutas) {
        if (ruta.propietarioId == -1) {
            ruta.mostrar();
            hayDisponibles = true;
        }
    }
    if (!hayDisponibles) {
        cout << "No hay más rutas disponibles para reclamar.\n";
    }
    cout << "-------------------------\n";
}

Ruta* Tablero::getRutaPorId(int id) {
    for (auto& ruta : rutas) {
        if (ruta.id == id) return &ruta;
    }
    return nullptr; 
}

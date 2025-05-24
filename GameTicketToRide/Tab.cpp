#include <iostream>
#include <iomanip>
using namespace std;

// Versión simplificada de colores para mejor compatibilidad
#define BG_WHITE  "\033[47m"
#define BG_RED    "\033[41m"
#define BG_BLUE   "\033[44m"
#define BG_GREEN  "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_PURPLE "\033[45m"
#define BG_CYAN   "\033[46m"
#define TEXT_BLACK "\033[30m"
#define TEXT_WHITE "\033[37m"
#define TEXT_BOLD  "\033[1m"
#define RESET     "\033[0m"

const int FILAS = 14;
const int COLUMNAS = 19;

struct Celda {
    string color;
    char letra;
};

void imprimirCelda(const Celda& celda) {
    cout << celda.color;
    if (celda.letra != ' ') {
        // Determinar color de texto basado en el fondo
        if (celda.color == BG_WHITE || celda.color == BG_YELLOW || celda.color == BG_GREEN) {
            cout << TEXT_BLACK << TEXT_BOLD << " " << celda.letra << " ";
        } else {
            cout << TEXT_WHITE << TEXT_BOLD << " " << celda.letra << " ";
        }
    } else {
        cout << "   "; // Tres espacios para mantener el formato
    }
    cout << RESET;
}

int main() {
    Celda tablero[FILAS][COLUMNAS];

    // Inicializar con fondo blanco
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero[i][j].color = BG_WHITE;
            tablero[i][j].letra = ' ';
        }
    }

    // Configurar áreas de color (usando colores básicos)
    // Azul
    for (int j = 0; j <= 7; ++j) tablero[7][j].color = BG_BLUE;
    for (int j = 10; j <= 15; ++j) tablero[4][j].color = BG_BLUE;
    for (int j = 8; j <= 11; ++j) tablero[7][j].color = BG_BLUE;

    // Verde
    for (int i = 4; i <= 7; ++i) tablero[i][5].color = BG_GREEN;
    for (int j = 14; j <= 16; ++j) tablero[2][j].color = BG_GREEN;
    for (int j = 11; j <= 15; ++j) tablero[8][j].color = BG_GREEN;

    // Amarillo (en lugar de naranja)
    for (int i = 8; i <= 11; ++i) tablero[i][5].color = BG_YELLOW;
    for (int j = 5; j <= 7; ++j) tablero[8][j].color = BG_YELLOW;
    for (int i = 5; i <= 8; ++i) tablero[i][15].color = BG_YELLOW;
    for (int j = 11; j <= 15; ++j) tablero[11][j].color = BG_YELLOW;

    // Rojo
    for (int i = 5; i <= 7; ++i) tablero[i][2].color = BG_RED;
    for (int j = 2; j <= 3; ++j) tablero[5][j].color = BG_RED;
    for (int i = 8; i <= 11; ++i) tablero[i][7].color = BG_RED;
    for (int j = 7; j <= 11; ++j) tablero[11][j].color = BG_RED;

    // Cyan (en lugar de marrón)
    for (int i = 1; i <= 4; ++i) tablero[i][5].color = BG_CYAN;
    for (int j = 2; j <= 5; ++j) tablero[13][j].color = BG_CYAN;
    for (int i = 11; i <= 13; ++i) tablero[i][18].color = BG_CYAN;

    // Morado
    for (int j = 10; j <= 12; ++j) tablero[6][j].color = BG_PURPLE;
    for (int i = 6; i <= 8; ++i) tablero[i][12].color = BG_PURPLE;
    for (int j = 15; j <= 18; ++j) tablero[6][j].color = BG_PURPLE;
    for (int i = 6; i <= 13; ++i) tablero[i][13].color = BG_PURPLE;

    // Letras
    tablero[7][0].letra = 'A';
    tablero[5][2].letra = 'B';
    tablero[13][2].letra = 'C';
    tablero[1][4].letra = 'D';
    tablero[4][5].letra = 'E';
    tablero[7][5].letra = 'F';
    tablero[11][5].letra = 'G';
    tablero[7][7].letra = 'H';
    tablero[6][10].letra = 'I';
    tablero[2][11].letra = 'J';
    tablero[7][11].letra = 'K';
    tablero[11][11].letra = 'L';
    tablero[13][13].letra = 'M';
    tablero[2][14].letra = 'N';
    tablero[4][15].letra = 'O';
    tablero[8][15].letra = 'P';
    tablero[11][15].letra = 'Q';
    tablero[6][18].letra = 'R';
    tablero[10][18].letra = 'S';

    // Imprimir el tablero
    cout << "   ";
    for (int j = 0; j < COLUMNAS; ++j) {
        cout << setw(3) << j;
    }
    cout << "\n";

    for (int i = 0; i < FILAS; ++i) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < COLUMNAS; ++j) {
            imprimirCelda(tablero[i][j]);
        }
        cout << RESET << endl;
    }

    // Leyenda de colores
    cout << "\nLEYENDA DE COLORES:\n";
    cout << BG_BLUE << TEXT_WHITE << " Azul " << RESET << " ";
    cout << BG_GREEN << TEXT_BLACK << " Verde " << RESET << " ";
    cout << BG_RED << TEXT_WHITE << " Rojo " << RESET << " ";
    cout << BG_YELLOW << TEXT_BLACK << " Amarillo " << RESET << " ";
    cout << BG_PURPLE << TEXT_WHITE << " Morado " << RESET << " ";
    cout << BG_CYAN << TEXT_BLACK << " Cyan " << RESET << " ";
    cout << BG_WHITE << TEXT_BLACK << " Blanco " << RESET << "\n";

    return 0;
}
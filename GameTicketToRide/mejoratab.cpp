#include <iostream>
#include <iomanip>
using namespace std;

// Definiciones de color ANSI
#define BG_RED    "\033[41m"
#define BG_BLUE   "\033[44m"
#define BG_GREEN  "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_WHITE  "\033[47m"
#define BG_PURPLE "\033[45m"
#define BG_CYAN   "\033[46m"
#define BG_ORANGE "\033[48;5;208m"
#define BG_GRAY   "\033[48;5;240m"
#define TEXT_BLACK "\033[30m"
#define TEXT_WHITE "\033[37m"
#define RESET     "\033[0m"

const int FILAS = 14;
const int COLUMNAS = 19;

struct Celda {
    string color = BG_WHITE;
    char letra = ' ';
};

void imprimirTablero() {
    Celda tablero[FILAS][COLUMNAS];

    // Punto DE (1,4) - Azul
    tablero[0][3].letra = 'D';
    tablero[0][4].color = BG_BLUE; // (1,5)
    tablero[0][5].color = BG_BLUE; // (1,6)
    tablero[1][5].color = BG_BLUE; // (2,6) - Corregido de (2,4) a (2,6)
    tablero[2][5].color = BG_BLUE; // (3,6)

    // Punto EF (4,6) - Verde
    tablero[3][5].letra = 'E';
    tablero[4][5].color = BG_GREEN; // (5,6)
    tablero[5][5].color = BG_GREEN; // (6,6)
    tablero[6][5].color = BG_GREEN; // (7,6)

    // Punto FG (8,6) - Rojo
    tablero[7][5].letra = 'F';
    tablero[8][5].color = BG_RED; // (9,6)
    tablero[9][5].color = BG_RED; // (10,6)
    tablero[10][5].color = BG_RED; // (11,6)

    // Punto GC (12,6) - Amarillo
    tablero[11][5].letra = 'G';
    tablero[11][4].color = BG_YELLOW; // (12,5)
    tablero[11][3].color = BG_YELLOW; // (12,4)
    tablero[11][2].color = BG_YELLOW; // (12,3)
    tablero[12][2].color = BG_YELLOW; // (13,3)

    // Punto C (14,3)
    tablero[13][2].letra = 'C';

    // Punto AB (8,1) - Morado
    tablero[7][0].letra = 'A';
    tablero[6][0].color = BG_PURPLE; // (7,1)
    tablero[5][0].color = BG_PURPLE; // (6,1)
    tablero[4][0].color = BG_PURPLE; // (5,1)
    tablero[4][1].color = BG_PURPLE; // (5,2)

    // Punto B (5,3)
    tablero[4][2].letra = 'B';

    // Punto AF (8,6) - Cyan (comparte posición con F)
    tablero[4][5].color = BG_CYAN; // (5,6)
    tablero[5][5].color = BG_CYAN; // (6,6)
    tablero[6][5].color = BG_CYAN; // (7,6)

    // Punto FH (8,9) - Naranja
    tablero[7][8].letra = 'H';
    tablero[7][6].color = BG_ORANGE; // (8,7)
    tablero[7][7].color = BG_ORANGE; // (8,8)

    // Punto HK (8,12) - Gris
    tablero[7][11].letra = 'K';
    tablero[7][9].color = BG_GRAY; // (8,10)
    tablero[7][10].color = BG_GRAY; // (8,11)

    // Punto KP (8,16) - Verde
    tablero[7][15].letra = 'P';
    tablero[7][12].color = BG_GREEN; // (8,13)
    tablero[7][13].color = BG_GREEN; // (8,14)
    tablero[7][14].color = BG_GREEN; // (8,15)

    // Punto PO (4,16) - Azul
    tablero[3][15].letra = 'O';
    tablero[6][15].color = BG_BLUE; // (7,16)
    tablero[5][15].color = BG_BLUE; // (6,16)
    tablero[4][15].color = BG_BLUE; // (5,16)

    // Punto OI (5,10) - Rojo
    tablero[4][9].letra = 'I';
    tablero[3][14].color = BG_RED; // (4,15)
    tablero[3][13].color = BG_RED; // (4,14)
    tablero[3][12].color = BG_RED; // (4,13)
    tablero[3][11].color = BG_RED; // (4,12)
    tablero[3][10].color = BG_RED; // (4,11)
    tablero[3][9].color = BG_RED; // (4,10)

    // Punto IK (5,10) - Amarillo
    tablero[5][9].color = BG_YELLOW; // (6,10)
    tablero[5][10].color = BG_YELLOW; // (6,11)
    tablero[5][11].color = BG_YELLOW; // (6,12)
    tablero[6][11].color = BG_YELLOW; // (7,12)

    // Punto KL (12,12) - Morado
    tablero[11][11].letra = 'L';
    tablero[11][10].color = BG_PURPLE; // (12,11)
    tablero[11][9].color = BG_PURPLE; // (12,10)
    tablero[11][8].color = BG_PURPLE; // (12,9)
    tablero[10][8].color = BG_PURPLE; // (11,9)
    tablero[9][8].color = BG_PURPLE; // (10,9)
    tablero[8][8].color = BG_PURPLE; // (9,9)

    // Punto ON (2,14) - Cyan
    tablero[1][13].letra = 'N';
    tablero[2][15].color = BG_CYAN; // (3,16)
    tablero[1][15].color = BG_CYAN; // (2,16)
    tablero[1][14].color = BG_CYAN; // (2,15)

    // Punto NJ (2,11) - Naranja
    tablero[1][10].letra = 'J';
    tablero[1][12].color = BG_ORANGE; // (2,13)
    tablero[1][11].color = BG_ORANGE; // (2,12)

    // Punto OR (6,19) - Gris
    tablero[5][18].letra = 'R';
    tablero[4][18].color = BG_GRAY; // (5,19)
    tablero[3][18].color = BG_GRAY; // (4,19)
    tablero[3][17].color = BG_GRAY; // (4,18)
    tablero[3][16].color = BG_GRAY; // (4,17)

    // Imprimir encabezado de columnas
    cout << "     ";
    for (int j = 0; j < COLUMNAS; ++j) {
        cout << setw(2) << j+1 << " ";
    }
    cout << "\n    " << string(COLUMNAS*3+1, '-') << endl;

    // Imprimir tablero
    for (int i = 0; i < FILAS; ++i) {
        cout << setw(2) << i+1 << " |";
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j].color;
            if (tablero[i][j].letra != ' ') {
                if (tablero[i][j].color == BG_YELLOW || tablero[i][j].color == BG_WHITE) {
                    cout << TEXT_BLACK << " " << tablero[i][j].letra << " ";
                } else {
                    cout << TEXT_WHITE << " " << tablero[i][j].letra << " ";
                }
            } else {
                cout << "   ";
            }
            cout << RESET;
        }
        cout << endl;
    }

    // Leyenda de colores
    cout << "\nLEYENDA DE COLORES:\n";
    cout << BG_BLUE << TEXT_WHITE << " Azul " << RESET << " ";
    cout << BG_GREEN << TEXT_WHITE << " Verde " << RESET << " ";
    cout << BG_RED << TEXT_WHITE << " Rojo " << RESET << " ";
    cout << BG_YELLOW << TEXT_BLACK << " Amarillo " << RESET << " ";
    cout << BG_PURPLE << TEXT_WHITE << " Morado " << RESET << " ";
    cout << BG_CYAN << TEXT_WHITE << " Cyan " << RESET << " ";
    cout << BG_ORANGE << TEXT_WHITE << " Naranja " << RESET << " ";
    cout << BG_GRAY << TEXT_WHITE << " Gris " << RESET << "\n";
}

int main() {
    imprimirTablero();
    return 0;
}
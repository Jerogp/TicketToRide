#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <map>
using namespace std;

#define BG_WHITE    "\033[47m"
#define BG_RED      "\033[41m"
#define BG_NARANJA  "\033[48;5:208m"
#define BG_BLUE     "\033[44m"
#define BG_GREEN    "\033[42m"
#define BG_PURPLE   "\033[45m"
#define BG_MARRON   "\033[48;5:94m"
#define TEXT_BLACK  "\033[30m"
#define TEXT_WHITE  "\033[37m"
#define TEXT_BOLD   "\033[1m"
#define RESET       "\033[0m"

const int FILAS = 15;
const int COLUMNAS = 20;

const map<string, string> COLORES_ANSI = {
    {"Rojo", BG_RED}, {"Azul", BG_BLUE}, {"Verde", BG_GREEN},
    {"Morado", BG_PURPLE}, {"Cafe", BG_MARRON}, {"Naranja", BG_NARANJA},
    {"Ninguno", BG_WHITE}
};

#endif
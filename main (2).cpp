#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <map>
#include <iomanip>
#include <limits>

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

using namespace std;

const int FILAS = 15;
const int COLUMNAS = 20;

const map<string, string> COLORES_ANSI = {
    {"Rojo", BG_RED}, {"Azul", BG_BLUE}, {"Verde", BG_GREEN},
    {"Morado", BG_PURPLE}, {"Cafe", BG_MARRON}, {"Naranja", BG_NARANJA},
    {"Ninguno", BG_WHITE}
};

struct Celda {
    string color;
    char letra;
};

struct CartaTren {
    string color;
    CartaTren(string c = "") : color(std::move(c)) {}

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
    Ciudad(string n = "") : nombre(std::move(n)) {}
};

struct Ruta {
    int id;
    string ciudad1, ciudad2;
    string color;
    int longitud;
    int puntos;
    int propietarioId = -1;

    Ruta(int _id, string c1, string c2, string col, int lon)
        : id(_id), ciudad1(std::move(c1)), ciudad2(std::move(c2)), color(std::move(col)), longitud(lon) {
        if (lon == 2) puntos = 1; else if (lon == 3) puntos = 2;
        else if (lon == 4) puntos = 4; else if (lon == 5) puntos = 6;
        else if (lon == 6) puntos = 9; else puntos = 0; 
    }

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

class Tablero {
    public:
    Celda board[FILAS][COLUMNAS];
    vector<Ruta> rutas;
    map<string, Ciudad> ciudades; 

    Tablero() {
        inicializarTableroBase(); 
        inicializarCiudadesYRutas(); 
        dibujarRutasEnTablero(); 
    }

    void inicializarTableroBase() {
        for (int i = 0; i < FILAS; ++i) { 
            for (int j = 0; j < COLUMNAS; ++j) {
                board[i][j] = {BG_WHITE, ' '};
            }
        }
        board[8][1] = {BG_WHITE, 'A'}; board[5][3] = {BG_WHITE, 'B'}; board[14][3] = {BG_WHITE, 'C'};
        board[1][4] = {BG_WHITE, 'D'}; board[4][6] = {BG_WHITE, 'E'}; board[8][6] = {BG_WHITE, 'F'};
        board[12][6] = {BG_WHITE, 'G'}; board[8][9] = {BG_WHITE, 'H'}; board[5][10] = {BG_WHITE, 'I'};
        board[2][11] = {BG_WHITE, 'J'}; board[8][12] = {BG_WHITE, 'K'}; board[12][12] = {BG_WHITE, 'L'};
        board[14][13] = {BG_WHITE, 'M'}; board[2][14] = {BG_WHITE, 'N'}; board[4][16] = {BG_WHITE, 'O'};
        board[8][16] = {BG_WHITE, 'P'}; board[12][16] = {BG_WHITE, 'Q'}; board[6][19] = {BG_WHITE, 'R'};
        board[10][19] = {BG_WHITE, 'S'};
    }

    void dibujarRutasEnTablero() {
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


    void inicializarCiudadesYRutas() {
        ciudades.emplace("A", Ciudad("A")); ciudades.emplace("B", Ciudad("B"));
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

    void actualizarGraficoRutaReclamada(int rutaId) {
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
            case 18: for (int j = 17; j <= 19; ++j) board[12][j].color = BG_WHITE; board[11][19].color = BG_WHITE; break;
            case 19: for (int j = 10; j <= 12; ++j) board[6][j].color = BG_WHITE; board[7][12].color = BG_WHITE; break;
            case 20: for (int j = 10; j <= 15; ++j) board[4][j].color = BG_WHITE; break;
            default: break;
        }
    }

    void imprimirCelda(const Celda& celda) const {
        cout << celda.color;
        if (celda.letra != ' ') {
            cout << TEXT_BLACK << TEXT_BOLD << " " << celda.letra << " ";
        } else {
            cout << "   "; 
        }
        cout << RESET;
    }

    void display() const {
        cout << "\n--- MAPA DEL TABLERO ---\n";
        cout << "    "; 
        for (int j = 1; j < COLUMNAS; ++j) {
            cout << setw(3) << j; 
        }
        cout << "\n";

        for (int i = 1; i < FILAS; ++i) {
            cout << setw(3) << i << " "; 
            for (int j = 1; j < COLUMNAS; ++j) {
                imprimirCelda(board[i][j]); 
            }
            cout << RESET << endl;
        }
        cout << "\nCOLOR DE LAS VIAS: ";
        for(const auto& par : COLORES_ANSI){
            if(par.first != "Ninguno" && par.second != BG_WHITE) { 
                cout << par.second << " " << par.first << " " << RESET << " ";
            }
        }
        cout << "\n" << endl;
    }

    void mostrarRutasDisponibles() const {
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
    Ruta* getRutaPorId(int id) {
        for (auto& ruta : rutas) {
            if (ruta.id == id) return &ruta;
        }
        return nullptr;
    }
};

class Mazo {
    public:
    vector<CartaTren> cartas;
    vector<CartaTren> descarte;
    mt19937 rng;

    Mazo() : rng(random_device{}()) {}

    void inicializar() {
        cartas.clear(); descarte.clear();
        const vector<string> colores = {"Rojo", "Azul", "Verde", "Morado", "Cafe", "Naranja"};
        for (const auto& color : colores) {
            for (int i = 0; i < 12; ++i) cartas.push_back(CartaTren(color));
        }
        barajar();
    }
    void barajar() { shuffle(cartas.begin(), cartas.end(), rng); }
    CartaTren robarCarta() {
        if (cartas.empty()) {
            if (descarte.empty()) throw runtime_error("Mazo y descarte vacios!");
            cout << "¡Barajando el mazo de descarte para reponer el mazo principal!\n";
            cartas = descarte; descarte.clear(); barajar();
             if (cartas.empty()) throw runtime_error("Mazo y descarte vacios despues de rebarajar!");
        }
        CartaTren carta = cartas.back(); cartas.pop_back(); return carta;
    }
    void agregarADescarte(const CartaTren& carta) { descarte.push_back(carta); }
    bool tieneCartasDisponibles() const { return !cartas.empty() || !descarte.empty(); }
};

class Jugador {
    public:
    int id;
    string nombre;
    vector<CartaTren> mano;
    int vagonesRestantes;
    int puntaje = 0;

    Jugador(int _id, string _nombre) : id(_id), nombre(std::move(_nombre)), vagonesRestantes(18) {}

    void tomarCarta(const CartaTren& carta) {
        mano.push_back(carta);
    }

    void mostrarMano() const {
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

    int contarCartas(const string& color) const {
        return count_if(mano.begin(), mano.end(), [&](const CartaTren& carta){
            return carta.color == color;
        });
    }

    bool tieneCartasSuficientes(const string& colorRuta, int cantidad) {
        return contarCartas(colorRuta) >= cantidad;
    }

    void jugarCartas(const string& colorRuta, int cantidad, Mazo& mazoDescarte) {
        int cartasParaDescartar = cantidad;
        auto it = mano.begin();
        while (it != mano.end() && cartasParaDescartar > 0) {
            if (it->color == colorRuta) {
                mazoDescarte.agregarADescarte(*it);
                it = mano.erase(it);
                cartasParaDescartar--;
            } else {
                ++it;
            }
        }
    }
};

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

JuegoDeTrenes(int numJugadores) {
   for (int i = 0; i < numJugadores; ++i) {
    jugadores.emplace_back(i, "Jugador " + to_string(i + 1));
  }
 }

    void iniciarJuego() {
        mazoPrincipal.inicializar();
        cartasVisibles.assign(NUM_CARTAS_VISIBLES, CartaTren("")); 

        for (int k = 0; k < NUM_CARTAS_VISIBLES; ++k) {
            try {
                if (mazoPrincipal.tieneCartasDisponibles()) {
                    cartasVisibles[k] = mazoPrincipal.robarCarta();
                }
            } catch (const runtime_error& e) {
                // Silencioso
            }
        }

        for (auto& jugador : jugadores) {
            for (int i = 0; i < 4; ++i) {
                if (mazoPrincipal.tieneCartasDisponibles()) {
                    try { jugador.tomarCarta(mazoPrincipal.robarCarta()); }
                    catch (const runtime_error& e) { break; } 
                } else { break; }
            }
        }
        tablero.display(); 
    }

    void rellenarCartasVisibles(int indiceSlot) {
        try {
            if (mazoPrincipal.tieneCartasDisponibles()) {
                cartasVisibles[indiceSlot] = mazoPrincipal.robarCarta();
            } else {
                cartasVisibles[indiceSlot] = CartaTren(""); 
            }
        } catch (const runtime_error& e) {
            cout << "No se pudo rellenar la carta visible: " << e.what() << endl;
            cartasVisibles[indiceSlot] = CartaTren("");
        }
    }

    void accionRobarCartas(Jugador& jugador) {
        cout << "\n--- Robar Cartas de Vagón ---\n";

        int cartasRobadasEsteTurno = 0;
        const int MAX_ROBOS_PERMITIDOS = 2;

        while(cartasRobadasEsteTurno < MAX_ROBOS_PERMITIDOS) {
            bool hayVisiblesTomables = false;
            for(size_t j = 0; j < cartasVisibles.size(); ++j) {
                if (!cartasVisibles[j].color.empty()) {
                    hayVisiblesTomables = true;
                    break;
                }
            }

            if (!hayVisiblesTomables) { 
                 cout << "No hay más cartas visibles para robar en este momento.\n";
                 break; 
            }

            cout << "\nCartas visibles (Robo " << (cartasRobadasEsteTurno + 1) << "/" << MAX_ROBOS_PERMITIDOS << "):\n";
            for(size_t j = 0; j < cartasVisibles.size(); ++j) {
                cout << "  " << (j + 1) << ". ";
                if (!cartasVisibles[j].color.empty()) {
                     cartasVisibles[j].mostrar();
                } else {
                    cout << "[VACÍO]";
                }
            }
            
            cout << "\nElige una carta visible (1-" << cartasVisibles.size() << "): ";
            int eleccionNum;
            cin >> eleccionNum;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Intenta este robo de nuevo.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (eleccionNum < 1 || eleccionNum > (int)cartasVisibles.size()) {
                cout << "Elección inválida. Elige un número de la lista de cartas visibles.\n";
                continue;
            }

            try {
                int indiceReal = eleccionNum - 1;
                if (cartasVisibles[indiceReal].color.empty()) {
                    cout << "No puedes tomar de una posición vacía. Elige de nuevo.\n";
                    continue;
                }

                CartaTren cartaTomada = cartasVisibles[indiceReal];
                jugador.tomarCarta(cartaTomada);
                cout << "Has tomado la carta: ";
                cartaTomada.mostrar();
                cout << endl;

                rellenarCartasVisibles(indiceReal);
                cartasRobadasEsteTurno++;

            } catch (const runtime_error& e) {
                cout << "Error durante el robo: " << e.what() << "\n";
                break;
            }
        }
    }
    
    void jugar() {
        iniciarJuego();
        while (!juegoTerminado) {
            turno(); 

            if (juegoTerminado) break; 

            bool jugadorConPocosVagones = false;
            for (const auto& jugador : jugadores) {
                if (jugador.vagonesRestantes <= 5) { 
                    jugadorConPocosVagones = true;
                    break;
                }
            }

            if (jugadorConPocosVagones && rondasFinales == 0) {
                cout << "\n¡Un jugador tiene 5 o menos vagones! Esta es la última ronda para todos los demás jugadores.\n";
                rondasFinales = jugadores.size(); 
            }

            if (rondasFinales > 0) {
                rondasFinales--; 
                if (rondasFinales == 0) {
                    juegoTerminado = true;
                    cout << "\n¡Fin de la ronda final! El juego ha terminado.\n";
                }
            }
        }
        determinarGanador();
    }

    void turno() {
        Jugador& jugadorActual = jugadores[jugadorActualIdx];
        bool accionPrincipalRealizada = false;

        while(!accionPrincipalRealizada && !juegoTerminado) { 
            cout << "\n==================================================\n";
            cout << "Turno de: " << TEXT_BOLD << jugadorActual.nombre << RESET << "\n";
            jugadorActual.mostrarMano();

            cout << "\nAcciones:\n";
            cout << "1. Robar cartas de Vagón\n";
            cout << "2. Realizar un trayecto\n";
            cout << "3. Mostrar el mapa\n";
            cout << "Elige una acción (1-3): ";
            int eleccion;
            cin >> eleccion;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Intenta de nuevo.\n";
                continue; 
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            switch(eleccion) {
                case 1:
                    accionRobarCartas(jugadorActual);
                    accionPrincipalRealizada = true; 
                    break;
                case 2:
                    accionPrincipalRealizada = accionReclamarRuta(jugadorActual);
                    break;
                case 3:
                    tablero.display();
                    break;
                default:
                    cout << "Opción inválida. Intenta de nuevo.\n";
                    break; 
            }
        }

        if (!juegoTerminado) {
             jugadorActualIdx = (jugadorActualIdx + 1) % jugadores.size();
        }
    }

bool accionReclamarRuta(Jugador& jugador) {
        tablero.mostrarRutasDisponibles();
        cout << "Ingresa el ID de la ruta a reclamar (o 0 para cancelar): ";
        int idRuta;
    cin >> idRuta;

    if (cin.fail()) { 
    cin.clear( ); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Entrada inválida. Por favor, introduce un número.\n"; 
    return false; 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    if (idRuta == 0) {
    cout << "Acción de reclamar ruta cancelada.\n";
    return false; 
    }

    Ruta* ruta = tablero.getRutaPorId(idRuta);
    if (!ruta) { 
    cout << "ID de ruta inválido.\n"; 
    return true; 
    }
    if (ruta->propietarioId != -1) { 
    cout << "Ruta ya reclamada.\n"; 
    return true; 
    }
    if (jugador.vagonesRestantes < ruta->longitud) { 
    cout << "No tienes suficientes vagones.\n"; 
    return true; 
    }

    if (jugador.tieneCartasSuficientes(ruta->color, ruta->longitud)) {
    jugador.jugarCartas(ruta->color, ruta->longitud, mazoPrincipal); 
    jugador.vagonesRestantes -= ruta->longitud;
    jugador.puntaje += ruta->puntos;
    ruta->propietarioId = jugador.id;

    cout << "\n¡Ruta " << ruta->ciudad1 << "-" << ruta->ciudad2 << " reclamada!\n";
    cout << "Ganas " << ruta->puntos << " puntos.\n";

    tablero.actualizarGraficoRutaReclamada(ruta->id); 
    tablero.display(); 
    } else {
        cout << "No tienes suficientes cartas " << ruta->color;
        cout << " (tienes " << jugador.contarCartas(ruta->color) << ", necesitas " << ruta->longitud << ").\n";
    }
    return true; 
}

void determinarGanador() {
        cout << "\n--- FIN DEL JUEGO ---\n";
        Jugador* ganador = nullptr;
        int maxPuntaje = -1;

        for (auto& jugador : jugadores) {
            cout << jugador.nombre << " terminó con " << jugador.puntaje << " puntos y " << jugador.vagonesRestantes << " vagones restantes.\n";
            if (jugador.puntaje > maxPuntaje) {
                maxPuntaje = jugador.puntaje;
                ganador = &jugador;
        }
    }
        if (ganador) {
            cout << "\n¡El ganador es " << TEXT_BOLD << ganador->nombre << RESET << " con " << ganador->puntaje << " puntos!\n";
        } else if (!jugadores.empty() && maxPuntaje != -1) { 
            vector<Jugador*> posiblesGanadores;
            for(auto& jugador : jugadores) {
                if(jugador.puntaje == maxPuntaje) {
                    posiblesGanadores.push_back(&jugador);
                }
            }
            if (posiblesGanadores.size() > 1) {
                cout << "\n¡Es un empate entre: ";
                for(size_t i=0; i < posiblesGanadores.size(); ++i) {
                    cout << TEXT_BOLD << posiblesGanadores[i]->nombre << RESET << (i == posiblesGanadores.size()-1 ? "" : ", ");
                }
                cout << " con " << maxPuntaje << " puntos!\n";
            } else if (posiblesGanadores.size() == 1) { 
                 cout << "\n¡El ganador es " << TEXT_BOLD << posiblesGanadores[0]->nombre << RESET << " con " << posiblesGanadores[0]->puntaje << " puntos!\n";
            } else {
                 cout << "\nNo se pudo determinar un ganador claro (situación inesperada).\n";
            }

        }
        else {
            cout << "\nNo hubo jugadores o no se registraron puntajes.\n";
        }
}
};

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
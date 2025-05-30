#include "Game.h"
using namespace std;

JuegoDeTrenes::JuegoDeTrenes(int numJugadores) {
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.emplace_back(i, "Jugador " + to_string(i + 1));
    }
}

// Inicializa el juego: configura el mazo, las cartas visibles y reparte las manos iniciales
void JuegoDeTrenes::iniciarJuego() {
    mazoPrincipal.inicializar();
    cartasVisibles.assign(NUM_CARTAS_VISIBLES, CartaTren("")); // Inicializa las cartas visibles como vacías

    // Roba cartas para llenar los espacios visibles
    for (int k = 0; k < NUM_CARTAS_VISIBLES; ++k) {
            if (mazoPrincipal.tieneCartasDisponibles()) {
                cartasVisibles[k] = mazoPrincipal.robarCarta();
            }
    }

    // Reparte 4 cartas iniciales a cada jugador
    for (auto& jugador : jugadores) {
        for (int i = 0; i < 4; ++i) {
            if (mazoPrincipal.tieneCartasDisponibles()) {
                try { jugador.tomarCarta(mazoPrincipal.robarCarta()); }
                catch (const runtime_error& e) { break; } // Si el mazo se vacía, detiene el reparto
            } else { break; }
        }
    }
    tablero.display(); // Muestra el tablero inicial
}

// Rellena un espacio de carta visible
void JuegoDeTrenes::rellenarCartasVisibles(int indiceSlot) {
        if (mazoPrincipal.tieneCartasDisponibles()) {
            cartasVisibles[indiceSlot] = mazoPrincipal.robarCarta();
        } else {
            cartasVisibles[indiceSlot] = CartaTren(""); // Si no hay más cartas, el slot queda vacío
        }
    
}

// Acción para que un jugador robe cartas
void JuegoDeTrenes::accionRobarCartas(Jugador& jugador) {
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

        // Manejo de entrada inválida
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
        
        int indiceReal = eleccionNum - 1; 

        CartaTren cartaTomada = cartasVisibles[indiceReal];
        jugador.tomarCarta(cartaTomada);
        cout << "Has tomado la carta: ";
        cartaTomada.mostrar();
        cout << endl;

        rellenarCartasVisibles(indiceReal); // Rellena el espacio vacío
        cartasRobadasEsteTurno++; // Incrementa el contador de robos
    }
}

void JuegoDeTrenes::jugar() {
    iniciarJuego(); 
    while (!juegoTerminado) {
        turno();

        if (juegoTerminado) break;

        // Verifica si algún jugador tiene 5 o menos vagones para activar las rondas finales
        bool jugadorConPocosVagones = false;
        for (const auto& jugador : jugadores) {
            if (jugador.vagonesRestantes <= 5) {
                jugadorConPocosVagones = true;
                break;
            }
        }

        if (jugadorConPocosVagones && rondasFinales == 0) {
            cout << "\nEsta es la última ronda para todos los demás jugadores.\n";
            rondasFinales = jugadores.size(); // Se establecen rondas finales igual al número de jugadores
        }

        if (rondasFinales > 0) {
            rondasFinales--;
            if (rondasFinales == 0) {
                juegoTerminado = true; // El juego termina al finalizar las rondas finales
                cout << "\n¡Fin de la ronda final! El juego ha terminado.\n";
            }
        }
    }
    determinarGanador();
}

// Lógica para un turno de jugador
void JuegoDeTrenes::turno() {
    Jugador& jugadorActual = jugadores[jugadorActualIdx];
    bool accionPrincipalRealizada = false; // Bandera para asegurar que se realice una acción principal

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
            continue; // Permite al jugador intentar de nuevo
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada

        switch(eleccion) {
            case 1:
                accionRobarCartas(jugadorActual); // Ejecuta la acción de robar cartas
                accionPrincipalRealizada = true; // Marca que se realizó una acción principal
                break;
            case 2:
                accionPrincipalRealizada = accionReclamarRuta(jugadorActual); // Ejecuta la acción de reclamar ruta
                break;
            case 3:
                tablero.display(); // Muestra el mapa
                break;
            default:
                cout << "Opción inválida. Intenta de nuevo.\n";
                break;
        }
    }

    // Pasa al siguiente jugador si el juego no ha terminado
    if (!juegoTerminado) {
        jugadorActualIdx = (jugadorActualIdx + 1) % jugadores.size();
    }
}

// Acción para que un jugador reclame una ruta
bool JuegoDeTrenes::accionReclamarRuta(Jugador& jugador) {
    tablero.mostrarRutasDisponibles(); // Muestra las rutas que pueden ser reclamadas
    cout << "Ingresa el ID de la ruta a reclamar (o 0 para cancelar): ";
    int idRuta;
    cin >> idRuta;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor, introduce un número.\n";
        return false; 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (idRuta == 0) {
        cout << "Acción de reclamar ruta cancelada.\n";
        return false;
    }

    Ruta* ruta = tablero.getRutaPorId(idRuta); // Obtiene la ruta por su ID
    if (!ruta) {
        cout << "ID de ruta inválido.\n";
        return false; 
    }
    if (ruta->propietarioId != -1) {
        cout << "Ruta ya reclamada.\n";
        return false; 
    }
    if (jugador.vagonesRestantes < ruta->longitud) {
        cout << "No tienes suficientes vagones.\n";
        return false; 
    }

    if (jugador.tieneCartasSuficientes(ruta->color, ruta->longitud)) {
        jugador.jugarCartas(ruta->color, ruta->longitud, mazoPrincipal); // Juega las cartas
        jugador.vagonesRestantes -= ruta->longitud; // Gasta los vagones
        jugador.puntaje += ruta->puntos; // Suma los puntos
        ruta->propietarioId = jugador.id; // Asigna la ruta al jugador

        cout << "\n¡Ruta " << ruta->ciudad1 << "-" << ruta->ciudad2 << " reclamada!\n";
        cout << "Ganas " << ruta->puntos << " puntos.\n";

        tablero.actualizarGraficoRutaReclamada(ruta->id); // Actualiza el gráfico del tablero
        tablero.display(); // Muestra el tablero actualizado
        
        return true;
    } else {
        cout << "No tienes suficientes cartas " << ruta->color;
        cout << " (tienes " << jugador.contarCartas(ruta->color) << ", necesitas " << ruta->longitud << ").\n";
        return false;
    }
}

void JuegoDeTrenes::determinarGanador() {
    cout << "\n--- FIN DEL JUEGO ---\n";
    Jugador* ganador = nullptr;
    int maxPuntaje = -1;

    // Encuentra el jugador con la puntuación más alta
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
        }
    }
}
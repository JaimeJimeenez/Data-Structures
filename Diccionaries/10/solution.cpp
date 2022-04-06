/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste.
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Jaime Jiménez Nieto
   Componente 2: Iván Pisonero Díaz
 */



 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>


using namespace std;

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada

//Coste lineal con respecto a max(N, C*T)
bool tratar_caso() {
    int N, C, T;

    cin >> N;
    cin >> C;

    if (N == 0 && C == 0) {
        return false;
    }

    unordered_map<string, int> estado;

    string jugador, buque, atacante, posAtacada;
    unordered_map<string, set<string>> tablero;  //Primera componente es posición, segunda es conjunto de jugadores en esa posición

    while (N--) {
        cin >> jugador;
        estado.insert({ jugador, C });

        for (int i = 0; i < C; i++) {
            cin >> buque;

            if (tablero.count(buque) == 0) {
                set<string> jugadores;
                jugadores.insert(jugador);
                tablero.insert({ buque, jugadores });
            }
            else {
                tablero.at(buque).insert(jugador);
            }
        }
    }

    bool hundido, vencido;

    cin >> T;
    while (T--) {
        set<string> atacados;
        hundido = false;
        vencido = false;

        cin >> atacante;
        cin >> posAtacada;

        if (tablero.count(posAtacada) != 0) {
            auto it = tablero.at(posAtacada).begin();

            while (it != tablero.at(posAtacada).end()) {
                if (*it != atacante) {
                    estado.at(*it)--;
                    if (estado.at(*it) == 0) {
                        vencido = true;
                        estado.erase(*it);
                    }
                    it = tablero.at(posAtacada).erase(it);
                    hundido = true;
                }
                else {
                    ++it;
                }
            }
        }

        if (vencido) {
            cout << "VENCIDO" << endl;
        }
        else if (hundido) {
            cout << "HUNDIDO" << endl;
        }
        else {
            cout << "AGUA" << endl;
        }
    }
    cout << "---" << endl;
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
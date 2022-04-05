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
  Componente 2: Ivan Pisonero Diaz
*/

// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;

void print(map<string, set<string>> juego) {
  for (auto it : juego) {
    auto jugadores = it.second;
    cout << it.first << " ";
    for (auto jugador : jugadores) {
      cout << jugador << " ";
    }
    cout << endl;
  }
}

void jugar(map<string, set<string>> &juego, map<string, int> &personas) {
  int T;
  cin >> T;

  string nombre, casilla;
  while (T--) {
    cin >> nombre >> casilla;
    bool hundido = false, vencido = false;
    auto jugadores = juego.at(casilla);

    for (auto jugador : jugadores) {
      if (jugador != nombre) {
        personas[jugador]--;
        if (personas[jugador] == 0) vencido = true;
        else hundido = true;
        juego.at(casilla).erase(jugador);
      }
    }
    juego.insert({ casilla, jugadores });

    if (vencido) cout << "VENCIDO\n";
    else if (hundido) cout << "HUNDIDO\n";
    else cout << "AGUA\n";
  }
}



bool tratar_caso() {
  int N, C, T;
  cin >> N >> C;
  if (N == 0 && C == 0) return false;

  map<string, set<string>> juego;
  map<string, int> jugadores;
  string nombre, casilla;
  while (N--) {
    cin >> nombre;

    jugadores.insert( { nombre, C });
    for (int i = 0; i < C; i++) {
      cin >> casilla;
      juego[casilla].insert( nombre );
    }
  }
  //print(juego);
  jugar(juego, jugadores);

  cout << "---\n";
  return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}


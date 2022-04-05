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

void jugar(map<string, set<string>> juego) {
  int T;
  cin >> T;

  while (T--) {
    string nombre, casilla;
    bool vencido = false, hundido = false;
    cin >> nombre >> casilla;

    for (auto jugador : juego) {
      if (jugador.first != nombre) {
        auto& casillas = juego.at(jugador.first);
        
        if (casillas.count(casilla) == 1) {
          casillas.erase(casilla);
          if (casillas.size() == 0) vencido = true;
          else hundido = true;
        }
      }
    }

    if (vencido) cout << "VENCIDO\n";
    else if (hundido) cout << "HUNDIDO\n";
    else cout << "AGUA\n";
  }
}

bool tratar_caso() {
  int N, C;
  cin >> N >> C;
  if (N == 0 && C == 0) return false;

  map<string, set<string>> juego;

  while (N--) {
    string nombre, casilla;
    cin >> nombre;

    for (int i = 0; i < C; i++) {
      cin >> casilla;
      juego[nombre].insert(casilla);
    }

  }

  jugar(juego);  
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


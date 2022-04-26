#include <iostream>
#include <fstream>
#include <string>

#include "MapTree.h"

using namespace std;

bool tratar_caso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    cin.ignore();

    MapTree<string, int> alumnos;
    string nombre, calificacion;

    while (N--) {
        getline(cin, nombre);
        getline(cin, calificacion);
        
        alumnos[nombre] += calificacion == "CORRECTO" ? 1 : -1;
    }

    for (auto const &it : alumnos) {
        if (it.value != 0) 
            cout << it.key << ", " << it.value << endl;
    }
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "MapTree.h"

using namespace std;

void print(const MapTree<string, int>& diccionario) {
    for (auto const& it : diccionario) {
        cout << it.key << " " << it.value;
    }
    cout << endl;
}

void actualizacion(MapTree<string, int> nuevo, MapTree<string, int> viejo) {
    vector<int> agregados, eliminados, modificados;

    for (auto it : nuevo) {
        if (viejo.contains(it.key)) {
            
        }
    }
}

void tratar_caso() {
    cin.ignore();

    string linea, p;
    getline(cin, linea);

    stringstream viejo(linea);

    MapTree<string, int> viejoDiccionario; 
    while (viejo >> p) {
        viejo >> viejoDiccionario[p];
    }

    getline(cin, linea);

    stringstream nuevo(linea);
    MapTree<string, int> nuevoDiccionario;
    while (nuevo >> p) {
        nuevo >> nuevoDiccionario[p];
    }

    actualizacion(nuevoDiccionario, viejoDiccionario);
    cout << "---\n";
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  int num_casos;
  cin >> num_casos;

  while (num_casos--) { tratar_caso(); }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
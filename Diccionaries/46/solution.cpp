#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "MapTree.h"

using namespace std;

void aMinusculas(string& palabra) {
    for (char c : palabra)
        c = tolower(c);
}

bool tratar_caso() {
    int num_lineas;
    cin >> num_lineas;
    if (num_lineas == 0) return false;

    cin.ignore();

    int i = 1;
    while (num_lineas--) {
        string linea;
        getline(cin, linea);

        MapTree<string, vector<int>> diccionario;
        string palabra;
        stringstream flujo(linea);

        while (flujo >> palabra) {
            aMinusculas(palabra);

            if (palabra.length() > 2) {
                vector<int>& lista_linea = diccionario[palabra];
                if (lista_linea.empty() || lista_linea.back() != i)
                    lista_linea.push_back(i);
            }
            i++;
        }
    }

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
#include <iostream>
#include <fstream>

#include "BinTree.h"

using namespace std;

tuple<int, int, int> nodo_cuadrado_mayor_prof_aux(const BinTree<int>& arbol) {
    if (arbol.empty()) return { -1, -1, 0 };

    auto [nodoIzq, profIzq, sumIzq] = nodo_cuadrado_mayor_prof_aux(arbol.left());
    auto [nodoDer, profDer, sumDer] = nodo_cuadrado_mayor_prof_aux(arbol.right());
    
    int suma = sumIzq + sumDer + arbol.root();
    if (profIzq == -1 && profDer == -1) {
        if (arbol.root() == sumIzq + sumDer) return { arbol.root(), 1, suma };
        else return { -1, -1, suma };
    }
    else if (profIzq >= profDer) return { nodoIzq, profIzq + 1, suma };
    else return { nodoDer, profDer + 1, suma };
}

int nodo_cuadrado_mayor_prof(const BinTree<int>& arbol) {
    return get<0>(nodo_cuadrado_mayor_prof_aux(arbol));
}


void tratar_caso() {
  BinTree<int> tree = read_tree<int>(std::cin);
  std::cout << nodo_cuadrado_mayor_prof(tree) << std::endl;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  int num_casos;
  std::cin >> num_casos;

  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
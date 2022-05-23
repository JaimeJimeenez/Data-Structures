#include <iostream>
#include <fstream>

#include "BinTree.h"

using namespace std;

pair<bool, int> arbol_de_equilibrio_aux(const BinTree<int> &arbol) {
    if (arbol.empty()) return { true, 0 };
    if (arbol.left().empty() && arbol.right().empty()) return { true, 1 };

    auto [equilIzq, hojasIzq] = arbol_de_equilibrio_aux(arbol.left());
    auto [equilDer, hojasDer] = arbol_de_equilibrio_aux(arbol.right());

    return { equilDer && equilIzq && hojasIzq - hojasDer == arbol.root(), hojasIzq + hojasDer };
}

bool arbol_de_equilibrio(const BinTree<int>& arbol) {
    return arbol_de_equilibrio_aux(arbol).first;
}

void tratar_caso() {
  BinTree<int> tree = read_tree<int>(std::cin);
  std::cout << (arbol_de_equilibrio(tree) ? "SI" : "NO") << std::endl;
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
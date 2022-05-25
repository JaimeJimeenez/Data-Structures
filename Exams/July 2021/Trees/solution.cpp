#include <iostream>
#include <fstream>

#include "BinTree.h"

using namespace std;

pair<bool, int> bien_codificado_aux(const BinTree<int> &arbol) {
    if (arbol.empty()) return { true, 0 };
    
    auto [codificadoIzq, cerosIzq] = bien_codificado_aux(arbol.left());
    auto [codificadoDer, cerosDer] = bien_codificado_aux(arbol.right());

    if (arbol.root() == 0)
        return { codificadoDer && codificadoIzq && abs(cerosIzq - cerosDer) <= 1, cerosIzq + cerosDer + 1 };
    else 
        return { codificadoDer && codificadoIzq && abs(cerosIzq - cerosDer) <= 1, cerosIzq + cerosDer };
}

bool bien_codificado(const BinTree<int> &arbol) {
    return bien_codificado_aux(arbol).first;
}

void tratar_caso() {
  BinTree<int> tree = read_tree<int>(std::cin);
  std::cout << (bien_codificado(tree) ? "SI" : "NO") << std::endl;
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
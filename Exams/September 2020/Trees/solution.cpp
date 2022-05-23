#include <iostream>
#include <fstream>
#include <tuple>

#include "BinTree.h"

using namespace std;

pair<bool, int> es_diestro_aux(const BinTree<int> &arbol) {
  if (arbol.empty()) return { true, 0 };
  if (arbol.left().empty() && arbol.right().empty()) return { true, arbol.root() };

  auto [esDiestroIzq, sumIzq] = es_diestro_aux(arbol.left());
  auto [esDiestroDer, sumDer] = es_diestro_aux(arbol.right());

  return { esDiestroDer && esDiestroIzq && sumDer > sumIzq, sumIzq + sumDer + arbol.root() } ;
}

bool es_diestro(const BinTree<int> &arbol) {
  return es_diestro_aux(arbol).first;
}

void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << (es_diestro(t) ? "SI" : "NO") << "\n";
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
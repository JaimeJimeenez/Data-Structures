#include <iostream>
#include <fstream>

#include "BinTree.h"

using namespace std;

template<typename T>
bool binary_search_aux(const BinTree<T>& arbol) {
  auto it_ant = arbol.begin();
  if (arbol.empty()) return true;
  auto it_sig = ++arbol.begin();

  while (it_sig != arbol.end() && *it_sig > *it_ant) {
    it_ant++;
    it_sig++;
  }

  return it_sig == arbol.end();
}

bool tratar_caso() {
  BinTree<int> t = read_tree<int>(cin);
  return binary_search_aux(t);
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
#include <iostream>
#include <fstream>

#include "BinTree.h"

using namespace std;

void perfilIzqAux(BinTree<int> const& arbol, int alt, int& altMax, vector<int>& perfil) {
  if (arbol.empty()) return;

  alt++;
  if (alt > altMax) {
    altMax = alt;
    perfil.push_back(arbol.root());
  }

  perfilIzqAux(arbol.left(), alt, altMax, perfil);
  perfilIzqAux(arbol.right(), alt, altMax, perfil);
}

vector<int> perfilIzq(BinTree<int> const& arbol) {
  vector<int> perfil;
  int altMax = 0;
  
  perfilIzqAux(arbol, 0, altMax, perfil);
  return perfil;
}

void tratar_caso() {
  BinTree<int> t = read_tree<int>(cin);
  vector<int> perfil = perfilIzq(t);

  for (auto elem : perfil) cout << elem << " ";
  cout << endl;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  int numCasos;
  cin >> numCasos;

  while (numCasos--)
    tratar_caso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}


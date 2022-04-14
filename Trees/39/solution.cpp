#include <iostream>
#include <vector>
#include <fstream>

#include "BinTree.h"

using namespace std;

BinTree<int> construir_aux(vector<int> const& preorden, vector<int> const& inorden, pair<int, int> p, pair<int, int> i) {
    if (p.first > p.second) return { };
    int raiz = preorden[p.first];
    int pRaiz = i.first;

    while (inorden[pRaiz] != raiz) ++pRaiz;

    int izqTam = pRaiz - i.first;
    auto izq = construir_aux(preorden, inorden, { p.first + 1, p.first + izqTam }, { i.first, pRaiz - 1 } );
    auto der = construir_aux(preorden, inorden, { p.first + 1 + izqTam, p.second}, { pRaiz + 1, i.second } );

    return { izq, raiz, der };
}

BinTree<int> construir(vector<int> const& preorden, vector<int> const& inorden) {
    return construir_aux(preorden, inorden, { 0, preorden.size() - 1}, { 0, inorden.size() - 1} );
}

bool tratar_caso() {
    int N;
    cin >> N;
    if (!cin) return false;
    
    vector<int> preorden(N);
    vector<int> inorden(N);
    for (int i = 0; i < N; i++)
        cin >> preorden[i];
    
    for (int i = 0; i < N; i++)
        cin >> inorden[i];

    BinTree<int> t = construir(preorden, inorden);
    t.display(cout);
    cout << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (tratar_caso());

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
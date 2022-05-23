#include <iostream>
#include <fstream>

#include "ListLinkedDouble.h"

using namespace std;

void tratar_caso() {
    int N, i, M, value;
    cin >> N >> i >> M;

    ListLinkedDouble<int> lista;
    while (N--) {
        cin >> value;
        lista.push_back(value);
    }

    lista.add_to(i, M);
    cout << lista << "\n";
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  int numCasos;
  cin >> numCasos;
  for (int i = 0; i < numCasos; i++)
    tratar_caso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
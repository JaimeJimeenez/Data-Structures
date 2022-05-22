#include <iostream>
#include <fstream>

#include "ListLinkedSingle.h"

using namespace std;

bool tratar_caso() {
    int N, pivot;
    cin >> N >> pivot;
    if (!cin) return false;

    int value;
    ListLinkedSingle<int> lista;
    while (N--) {
        cin >> value;
        lista.push_back(value);
    }

    lista.partition(pivot);
    lista.display();
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
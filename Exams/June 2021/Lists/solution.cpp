#include <iostream>
#include <fstream>

#include "ListLinkedDouble.h"

using namespace std;

void tratar_caso() {
    ListLinkedDouble<int> lista;
    int value;

    cin >> value;
    while (value != 0) {
        lista.push_back(value);
        cin >> value;
    }

    ListLinkedDouble<int> other;
    cin >> value;
    while (value != 0) {
        other.push_back(value);
        cin >> value;
    }

    lista.unzip(other);
    cout << lista << "\n";
    cout << other << "\n";
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;
    while (num_casos--) tratar_caso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

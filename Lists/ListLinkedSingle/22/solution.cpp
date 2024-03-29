#include <iostream>
#include <fstream>
#include "ListLinkedSingle.h"

using namespace std;

void tratar_caso() {
  int N, value;
  cin >> N;

  ListLinkedSingle<int> list;
  while (N--) {
    cin >> value;
    list.push_back(value);
  }

  cin >> N;
  ListLinkedSingle<int> other;
  while (N--) {
    cin >> value;
    other.push_back(value);
  }

  list.unzip(other);
  cout << list << "\n";
  cout << other << "\n";
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
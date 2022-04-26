#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool tratar_caso() {
    int M;
    cin >> M;

    unordered_map<int, int> capitulos;
    int capitulo;
    int max = 0;
    int noVistos = 0;

    for (int i = 0; i < M; i++) {
        cin >> capitulo;
        if (!capitulos.count(capitulo)) noVistos++;
        else {
            if (i - noVistos > capitulos[capitulo]) noVistos++;
            else noVistos = i - capitulos[capitulo];
        }
        capitulos[capitulo] = i;
        max = std::max(max, noVistos);
    }

    cout << max << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int numCasos;
    cin >> numCasos;
    while (numCasos--) tratar_caso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
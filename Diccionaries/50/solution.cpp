#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void maximumCapitulos(const map<int, int>& series) {
    for (auto const& it : series)
        cout << it.second << endl;
}

bool tratar_caso() {
    int N, M;
    cin >> N;
    if (!cin) return false;

    map<int, int> series;
    for (int i = 0; i < N; i++) {
        cin >> M;
        
        series[i] = 0;

        set<int> capitulos;
        int capitulo;
        int maximum = 0;
        while (M--) {
            cin >> capitulo;
            maximum++;
            if (capitulos.count(capitulo) == 0) {
                capitulos.insert(capitulo);
                
            }
            else {
                series.at(i) = max(series[i], maximum);
                maximum = 0;
            }
        }
    }
    maximumCapitulos(series);
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
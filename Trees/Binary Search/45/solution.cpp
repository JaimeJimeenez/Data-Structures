#include <iostream>
#include <fstream>
#include <vector>

#include "SetTree.h"

using namespace std;

bool tratar_caso() {
    int N, M;
    cin >> N;
    if (N == 0) return false;

    int value;
    SetTree<int> tree;
    while (N--) {
        cin >> value;
        tree.insert(value);
    }

    cin >> M;
    vector<int> v;
    while (M--) {
        cin >> value;
        v.push_back(value);
    }

    pair<bool, int> pair;
    for (auto const& elem : v) {
        pair = tree.lower_bound(elem);
        if (pair.first) cout << pair.second;
        else cout << "NO HAY";
        cout << "\n";
    }

    cout << "---\n";
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
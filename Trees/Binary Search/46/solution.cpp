#include <iostream>
#include <fstream>
#include <vector>

#include "SetTree.h"

using namespace std;

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    int menor;
    cin >> menor;
    if (opcion == "N") {
        vector<int> v;
        int value;

        cin >> value;
        while (value != -1) {
            v.push_back(value);
            cin >> value;
        }

        sort(v.begin(), v.end(), greater<int>());
        
        SetTree<int> tree;
        for (auto const& elem : v) tree.insert(elem);
        cout << tree << "\n";
    }
    else {
        vector<string> v;
        string value;

        cin >> value;
        while (value != "FIN") {
            v.push_back(value);
            cin >> value;    
        }
        sort(v.begin(), v.end(), greater<string>());

        SetTree<string> tree;
        for (auto const& elem : v) tree.insert(elem);
        cout << tree << "\n";
    }

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
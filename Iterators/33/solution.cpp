#include <iostream>
#include <fstream>

#include "ListLinkedDouble.h"

using namespace std;

void tratar_caso() {
    ListLinkedDouble<int> list;
    int value;
    cin >> value;

    while (value != 0) {
        list.push_back(value);
        cin >> value;
    }

    auto it_inverso = list.rbegin(); it_inverso.advance();
    while (it_inverso != --list.rend() ) {
        cout << it_inverso.elem() << " ";
        it_inverso.advance();
    }
    cout << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;

    while (num_casos--) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
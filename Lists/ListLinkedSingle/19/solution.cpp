#include <iostream>
#include <cassert>
#include <fstream>

#include "ListLinkedSingle.h"

using namespace std;

bool tratar_caso() {
    int N, L, P;
    cin >> N >> L >> P;
    if (!cin) return false;

    ListLinkedSingle lista;
    int valor;
    while (N--) {
        cin >> valor;
        lista.push_back(valor);
    }

    lista.reverseSegment(L, P);
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
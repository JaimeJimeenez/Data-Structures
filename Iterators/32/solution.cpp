#include <iostream>
#include <fstream>
#include <list>

using namespace std;

bool es_toeplitz(const list<list<int>> &matriz) {
    auto it_lista = matriz.begin();
    auto it_aux = it_lista;

    while (it_lista != --matriz.end()) {
        list<int> current = *it_aux;
        list<int> next = *(++it_aux);
        auto it_current = current.begin();
        auto it_next = ++next.begin();

        while (it_next != next.end()) {
            if (*it_current != *it_next) return false;
            ++it_next; ++it_current;
        }

        ++it_lista;
    }

    return true;
}

bool tratar_caso() {
    list<list<int>> matriz;
    int value;
    cin >> value;
    if (value == 0) return false;

    while (value != 0) {
        list<int> lista;
        while (value != 0) {
            lista.push_back(value);
            cin >> value;
        }
        matriz.push_back(lista);
        cin >> value;
    }

    cout << (es_toeplitz(matriz) ? "SI" : "NO") << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool tratar_caso() {
    string linea;
    char comando;
    getline(cin, linea);
    if (!cin) return false;

    stringstream flujo(linea);
    string secuencia;

    auto it = linea.begin();
    auto cursor = secuencia.begin();

    while (flujo >> comando) {
        if (comando == '+') 
            cursor = secuencia.end();
        else if (comando == '-') 
            cursor = secuencia.begin();
        else if (comando == '*')
            ++cursor;
        else if (comando == '3') 
            cursor = secuencia.erase(cursor);
        else {
            secuencia.insert(cursor, comando);
            ++cursor;
        }
    }

    cout << secuencia << endl;
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
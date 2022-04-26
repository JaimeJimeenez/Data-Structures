#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <queue>
#include <string>

using namespace std;

bool esVocal(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void volcar(string& decodificado, stack<char>& pila) {
    while (!pila.empty()) {
        char c = pila.top(); 
        pila.pop();
        decodificado += c;
    }
}

string decodificacion(const string& mensaje) {
    stack<char> pila;
    queue<char> cola;
    string decodificado;
    bool primero = true;

    for (auto &c : mensaje) {
        if (primero)
            pila.push(c);
        else
            cola.push(c);
        primero = !primero;
    }

    while (!pila.empty()) {
        cola.push(pila.top());
        pila.pop();
    }

    while (!cola.empty()) {
        char c = cola.front();
        cola.pop();
        if (!esVocal(c))
            pila.push(c);
        else {
            volcar(decodificado, pila);
            decodificado += c;
        }
    }
    volcar(decodificado, pila);

    string aux;
    for (int i = decodificado.size() - 1; i >= 0; i--)  
        aux.push_back(decodificado[i]);
    decodificado = aux;
    
    return decodificado;
}

bool tratar_caso() {
    string mensaje;
    getline(cin, mensaje);

    if (!cin)
        return false;

    cout << decodificacion(mensaje) << endl;
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


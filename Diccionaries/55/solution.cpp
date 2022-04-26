#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

void tratar_caso() {
    int num_linea;
    cin >> num_linea;

    vector<pair<string, int>> programa;
    unordered_map<int, int> diccionario;

    int cont = 10;

    while (num_linea != 0) {
        string instruccion;
        cin >> instruccion;
        int salto;
        if (instruccion == "GOTO" || instruccion == "GOSUB") cin >> salto;
        programa.push_back( { instruccion, salto });
        diccionario[num_linea] = cont;
        cont += 10;
        cin >> num_linea;
    }

    cont = 10;
    for (auto const& instruccion : programa) {
        cout << cont << " " << instruccion.first;
        if (instruccion.first == "GOTO" || instruccion.first == "GOSUB")
            cout << " " << diccionario[instruccion.second];
        cout << endl;
        cont += 10;
    }

    cout << "---\n";
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
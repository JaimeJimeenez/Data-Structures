#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

void bingo(const map<int, set<string>> &cartones, map<string, int>& jugadores) {
    bool bingo = false;
    int bola;

    while (!bingo) {
        cin >> bola;
        if (cartones.count(bola) == 1) {
            auto& carton = cartones.at(bola);
            for (auto elem : carton) {
                jugadores[elem]--;
                if (jugadores[elem] == 0) bingo = true;
            }
        }
    }

    for (auto const& it : jugadores)
        if (it.second == 0) cout << it.first << " ";
    cout << endl;
}

bool tratar_caso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    map<int, set<string>> cartones;
    map<string, int> jugadores;
    while (N--) {
        string nombre;
        int valor;
        cin >> nombre;

        set<int> numeros;
        cin >> valor;
        while (valor != 0) {
            cartones[valor].insert(nombre);
            jugadores[nombre]++;
            cin >> valor;
        }
    }

    bingo(cartones, jugadores);
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
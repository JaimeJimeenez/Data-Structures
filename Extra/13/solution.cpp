#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Hora {
private:
    int horas, minutos, segundos;

public:
    Hora() { };
    Hora(int h, int m, int s) : horas(h), minutos(m), segundos(s) {
        if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
            throw invalid_argument("ERROR");
    };

    bool operator<(Hora const& other) const {
        return (3600 * horas + 60 * minutos + segundos) < (3600 * other.horas + 60 * other.minutos + other.segundos) ;
    }

    int getHoras() const { return horas; }
    int getMinutos() const { return minutos; }
    int getSegundos() const { return segundos; }

};

void print(Hora const& hora) {
    cout << setfill('0') << setw(2) << hora.getHoras() << ':' << setfill('0') << setw(2) << hora.getMinutos() << ':' << setfill('0') << setw(2) << hora.getSegundos();
}

bool tratar_caso() {
    int nTrenes, nHoras;
    cin >> nTrenes >> nHoras;
    if (nTrenes == 0 && nHoras == 0)
        return false;
    
    vector<Hora> trenes(nTrenes);
    int horas, minutos, segundos;
    char c;

    for (int i = 0; i < nTrenes; i++) {
        cin >> horas >> c >> minutos >> c >> segundos;
        trenes[i] = { horas, minutos, segundos };
    }

    for (int i = 0; i < nHoras; i++) {
        cin >> horas >> c >> minutos >> c >> segundos;
        Hora actual = { horas, minutos, segundos };
        auto lower = lower_bound(trenes.begin(), trenes.end(), actual);
        
        if (lower == trenes.end())
            cout << "NO";
        else
            print(*lower);
        
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

    while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
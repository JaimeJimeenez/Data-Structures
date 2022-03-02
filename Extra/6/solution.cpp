#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX = 1000;

class Hora {
private:
    int horas, minutos, segundos;

public:
    Hora() { };
    Hora(int horas, int minutos, int segundos) : horas(horas), minutos(minutos), segundos(segundos) { };

    bool operator<(Hora const& other) const {
        return (3600 * horas + 60 * minutos + segundos) <= (3600 * other.horas + 60 * other.minutos + other.segundos);
    }

    int getHoras() const { return horas; }
    int getMinutos() const { return minutos; }
    int getSegundos() const { return segundos; }

};

inline std::ostream& operator<<(std::ostream& out, const Hora& h) {
    out << setfill('0') << setw(2) << h.getHoras() << ":" << setfill('0') << setw(2) << h.getMinutos() << ":" << setfill('0') << setw(2) << h.getSegundos() << endl;
    return out;
}
bool tratar_caso() {
    int nTrenes, nHoras;
    cin >> nTrenes >> nHoras;
    if (nTrenes == 0 && nHoras == 0)
        return false;
    
    Hora v[MAX];
    int horas, minutos, segundos;
    char c;
    bool encontrado = false;
    int j = 0;

    for (int i = 0; i < nTrenes; i++) {
        cin >> horas >> c >> minutos >> c >> segundos;
        v[i] = {horas, minutos, segundos};
    }

    while (nHoras--) {
        cin >> horas >> c >> minutos >> c >> segundos;
        Hora hActual(horas, minutos, segundos);
        int j = 0;
        while (!encontrado && j < nTrenes) {
            if (hActual < v[j]) {
                cout << v[j];
                encontrado = true;
            }
            j++;
        }
        if (!encontrado)
            cout << "NO\n";
        encontrado = false;
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
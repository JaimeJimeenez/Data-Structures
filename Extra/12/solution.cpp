#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>

using namespace std;

typedef pair<int, int> monomio;

class Polinomio {
private:
    vector<monomio> monomios;
public:
    Polinomio() { };

    int binarySearch(int init, int fin, const monomio& monomio) {
        if (init == fin)
            return init;
        else {
            int mitad = (init + fin) / 2;
            if (monomios[mitad].second > monomio.second)
                return binarySearch(init, mitad, monomio);
            else if (monomios[mitad].second < monomio.second)
                return binarySearch(mitad + 1, fin, monomio);
            else {
                monomios[mitad].first += monomio.first;
                return -1;
            }
        }
    }

    void anyadir_monomio(const monomio& monomio) {
        int pos = binarySearch(0, monomios.size(), monomio);
        if (pos != -1)
            monomios.insert(monomios.begin() + pos, monomio);
    }

    int evaluar(int valor) const {
        int res = 0;

        for (auto monomio : monomios)
            res += monomio.first * pow(valor, monomio.second);

        return res;
    }
};

bool tratar_caso() {
    int coef, exp;
    cin >> coef >> exp;
    if (!cin)
        return false;
    
    Polinomio p;
    while (coef != 0 || exp != 0) {
        if (coef != 0)
            p.anyadir_monomio( { coef, exp });
        cin >> coef >> exp;
    }

    int casos, valor;
    cin >> casos;
    while (casos--) {
        cin >> valor;
        cout << p.evaluar(valor) << " ";
    }

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
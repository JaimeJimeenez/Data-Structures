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

    void anyadir_monomio(const monomio& nuevoMonomio) {
        if (nuevoMonomio.first != 0) {
            auto it = lower_bound(monomios.begin(), monomios.end(), nuevoMonomio, 
                [](const monomio& m, const monomio& r) {
                return m.second < r.second;
            });
            if (it >= monomios.begin() && it < monomios.end() && nuevoMonomio.second == (*it).second)
                (*it).first += nuevoMonomio.first;
            else
                monomios.insert(it, nuevoMonomio);
        }
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
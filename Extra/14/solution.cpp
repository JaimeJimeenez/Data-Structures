#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

class Complejo {
private:
    float real, imaginaria;

public:
    Complejo() { };
    Complejo(float r, float i) : real(r), imaginaria(i) { };

    Complejo operator+(Complejo const& other) const {
        float r = real + other.real;
        float i = imaginaria + other.imaginaria;

        return { r, i };
    }

    Complejo operator*(Complejo const& other) const {
        float r = (real * other.real) - (imaginaria * other.imaginaria);
        float i = (real * other.imaginaria) + (other.real * imaginaria);

        return { r, i };
    }

    float getReal() const { return real; };
    float getImaginaria() const { return imaginaria; };

    int modulo() { return sqrt(pow(real, 2) + pow(imaginaria, 2)); };
};

bool esModulo(const Complejo& complejo, int it) {
    int i = 1;
    Complejo z(0, 0);

    while(i < it) {
        z = z * z + complejo;
        if (z.modulo() > 2)
            return false;
        i++;    
    }

    return true;
} 

void tratar_caso() {
    int it;
    float r, i;
    cin >> r >> i >> it;

    Complejo c(r, i);
    cout << (esModulo(c, it) ? "SI" : "NO") << endl;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    while (numCasos--)
        tratar_caso();

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
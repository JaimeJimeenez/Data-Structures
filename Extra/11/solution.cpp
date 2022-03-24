#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
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
    }

    bool operator<(Hora const& other) const {
        return 3600 * horas + 60 * minutos + segundos <= 3600 * other.horas + 60 * other.minutos + other.segundos;
    }

    Hora operator+(Hora const& other) const {
        int sumaH = horas + other.horas;
        int sumaM = minutos + other.minutos;
        int sumaS = segundos + other.segundos;

        if (sumaS > 59) {
            sumaM++;
            sumaS -= 60;
        }

        if (sumaM > 59) {
            sumaH++;
            sumaM -= 60;
        }

        Hora hr(sumaH, sumaM, sumaS);
        return hr;
    }

    bool operator==(Hora const& other) const {
        return (horas * 3600 + minutos * 60 + segundos == other.horas * 3600 + other.minutos * 60 + other.segundos);
    }

    int getHoras() const { return horas; }
    int getMinutos() const { return minutos; }
    int getSegundos() const { return segundos; }
};

class Pelicula {
private:
    Hora comienzo, duracion, fin;
    string titulo;

public:
    Pelicula() { };
    Pelicula(Hora hc, Hora d, string t) : comienzo(hc), duracion(d), titulo(t) { };
    Pelicula(Hora f, string t) : fin(f), titulo(t) { };

    Hora getComienzo() const { return comienzo; };
    Hora getDuracion() const { return duracion; };
    Hora getFin() const { return fin; };
    string getTitulo() const { return titulo; };

    bool operator< (Pelicula const& other) const {
        
        if (fin.getHoras() < other.getFin().getHoras())
            return true;
        else if (fin.getHoras() == other.getFin().getHoras()) {
            if (fin.getMinutos() < other.getFin().getMinutos())
                return true;
            else if (fin.getMinutos() == other.getFin().getMinutos()) {
                if (fin.getSegundos() < other.getFin().getSegundos())
                    return true;
                else if (fin.getSegundos() == other.getFin().getSegundos())
                    if (titulo < other.getTitulo())
                        return true;
            }
        }

        return false;
    }

};

void inserta(Pelicula p, vector<Pelicula>& v) {
    int i = v.size();

    while (i > 0 && p < v[i - 1]) {
        if (i == v.size())
            v.push_back(v[i - 1]);
        else
            v[i] = v[i - 1];
        i--;
    }

    while (i > 0 && p.getFin() == v[i - 1].getFin() && p.getTitulo() < v[i - 1].getTitulo()) {
        if (i == v.size())
            v.push_back(v[i - 1]);
        else
            v[i] = v[i - 1];
        i--;
    }

    if (i == v.size())
        v.push_back(p);
    else 
        v[i] = p;
}

void printHora(Hora const& h) {
    cout << setfill('0') << setw(2) << h.getHoras() << ':' << setfill('0') << setw(2) << h.getMinutos() << ':' << setfill('0') << setw(2) << h.getSegundos();
} 

void printPelicula(Pelicula const& p) {
    printHora(p.getFin());
    cout << " " << p.getTitulo();
}

bool tratar_caso() {
    int peliculas;
    cin >> peliculas;
    if (peliculas == 0)
        return false;

    int h1, m1, s1, h2, m2, s2;
    char c;
    string titulo;
    vector<Pelicula> v;

    try {
        
        for (int i = 0; i < peliculas; i++) {
            cin >> h1 >> c >> m1 >> c >> s1;
            cin >> h2 >> c >> m2 >> c >> s2;
            getline(cin, titulo);

            Hora comienzo(h1, m1, s1);
            Hora duracion(h2, m2, s2);
            Pelicula p(comienzo, duracion, titulo);

            Hora sum = p.getComienzo() + p.getDuracion();
            Pelicula pS(sum, p.getTitulo());
            inserta(pS, v);
        }

        for (int i = 0; i < peliculas; i++) {
            printPelicula(v[i]);
            cout << endl;
        }
        
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
    }

    
    cout << "---" << endl;
    v.clear();
    
    return true;
}

void solucion() {
    int peliculas, h1, m1, s1, h2, m2, s2;
    char c;
    string titulo;
    vector<Pelicula> v;

    cin >> peliculas;
    while (peliculas != 0) {
        
        cin >> peliculas;
    }
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
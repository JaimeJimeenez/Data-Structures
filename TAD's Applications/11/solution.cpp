/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste de las operaciones
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Jaime Jiménez Nieto
   Componente 2: Ivan Pisonero Diaz
 */


 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <map>
#include <unordered_map>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

class Desierto {
public:

    Desierto() { }

    void anyadir_torre(const string& nombre, int x, int y) {
        if (torres.count(nombre))
            throw std::domain_error("Torre ya existente");
        if (direcciones.count({ x, y }))
            throw std::domain_error("Posicion ocupada");

        torres.insert({ nombre, { x, y } });
        direcciones.insert({ { x, y }, nombre });
    }

    void eliminar_torre(const string& nombre) {
        if (torres.count(nombre) == 0)
            throw std::domain_error("Torre no existente");

        direcciones.erase(torres[nombre]);
        torres.erase(nombre);
    }

    pair<bool, string> torre_en_posicion(int x, int y) const {
        if (direcciones.count({ x, y })) return { true, direcciones.at({ x, y }) };
        return { false, "" };
    }

    pair<int, int> posicion(const string& nombre) const {
        if (torres.count(nombre) == 0)
            throw std::domain_error("Torre no existente");

        return torres.at(nombre);
    }

    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
        if (torres.count(nombre) == 0)
            throw std::domain_error("Torre no existente");

        auto [x, y] = torres.at(nombre);
        auto it = direcciones.find({ x, y });

        if (dir == Direccion::Norte || dir == Direccion::Este) {
            while (it != direcciones.end()) {
                if (dir == Direccion::Norte && it->first.first > x) return "No hay torres en esa direccion";
                if (dir == Direccion::Norte && it->first.second > y) return it->second;
                if (dir == Direccion::Este && it->first.first > x && it->first.second == y) return it->second;
                it++;
            }
        }
        else {
            while (it != --direcciones.begin()) {
                if (dir == Direccion::Sur && it->first.first < x) return "No hay torres en esa direccion";
                if (dir == Direccion::Sur && it->first.second < y) return it->second;
                if (dir == Direccion::Oeste && it->first.first < x && it->first.second == y) return it->second;
                it--;
            }
        }

        return "No hay torres en esa direccion";
    }


private:
    unordered_map<string, pair<int, int>> torres;
    map<pair<int, int>, string> direcciones;
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Desierto desierto;
    Direccion dir;
    string nombre;
    int x, y;
    while (opcion != "FIN") {
        try {

            if (opcion == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (opcion == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (opcion == "torre_en_posicion") {
                cin >> x >> y;
                auto [hayTorre, torre] = desierto.torre_en_posicion(x, y);

                if (hayTorre) cout << "SI " << torre << "\n";
                else cout << "NO\n";
            }
            else if (opcion == "posicion") {
                cin >> nombre;
                auto [corX, corY] = desierto.posicion(nombre);
                cout << corX << " " << corY << endl;
            }
            else if (opcion == "torre_mas_cercana") {
                cin >> nombre >> dir;
                cout << desierto.torre_mas_cercana(nombre, dir) << "\n";
            }

        }
        catch (std::domain_error& exception) {
            cout << exception.what() << "\n";
        }

        cin >> opcion;
    }

    cout << "---\n";
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

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class CarnetPuntos {
public:

    void nuevo(const string& dni) {
        if (conductores.count(dni)) throw
            domain_error("Conductor duplicado");
        
        conductores[dni] = 15;
        puntosTotales[15]++;
    }

    void quitar(const string& dni, int puntos) {
        if (!conductores.count(dni)) throw
            domain_error("Conductor inexistente");
        
        puntosTotales[conductores[dni]]--;

        if (conductores[dni] - puntos < 0) conductores[dni] = 0;
        else conductores[dni] = conductores[dni] - puntos;
        
        puntosTotales[conductores[dni]]++;
    }

    int consultar(const string& dni) const {
        if (!conductores.count(dni)) throw
            domain_error("Conductor inexistente");
        
        return conductores.at(dni);
    }

    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) throw 
            domain_error("Puntos no validos");
        
        return (puntosTotales.count(puntos)) ? puntosTotales.at(puntos) : 0;
    }

private:
    unordered_map<string, int> conductores;
    unordered_map<int, int> puntosTotales;
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    CarnetPuntos carnet;
    string dni;
    int puntos;
    while (opcion != "FIN") {

        try {
            if (opcion == "nuevo") {
                cin >> dni;
                carnet.nuevo(dni);
            }
            else if (opcion == "cuantos_con_puntos") {
                cin >> puntos;
                int cuantos = carnet.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay " << cuantos << "\n";
            }
            else if (opcion == "quitar") {
                cin >> dni >> puntos;
                carnet.quitar(dni, puntos);
            }
            else if (opcion == "consultar") {
                cin >> dni;
                int consultados = carnet.consultar(dni);
                cout << "Puntos de " << dni << ": " << consultados << "\n";
            }
            
        } catch (std::domain_error &exception) {
            cout << "ERROR: " << exception.what() << endl;
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

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>

using namespace std;

class CarnetPuntos {
public:

    void nuevo(const string& dni) {
        if (conductores.count(dni)) throw
            domain_error("Conductor duplicado");
        
        puntosConductores[15].push_front(dni);
        conductores[dni].puntos = 15;
        conductores[dni].it = puntosConductores[15].begin();
    }

    void quitar(const string& dni, int puntos) {
        InfoConductor& info = buscar_conductor(dni);
        
        if (info.puntos != 0) {
            puntosConductores[info.puntos].erase(info.it);
            if (info.puntos < puntos) {
                puntosConductores[0].push_front(dni);
                info.puntos = 0;
                info.it = puntosConductores[0].begin();
            }
            else {
                int restantes = info.puntos - puntos;
                puntosConductores[restantes].push_front(dni);
                info.puntos = restantes;
                info.it = puntosConductores[restantes].begin();
            }
        }
        
    }

    void recuperar(const string& dni, int puntos) {
        InfoConductor& info = buscar_conductor(dni);
        
        if (info.puntos != 15) {
            puntosConductores[info.puntos].erase(info.it);
            if (info.puntos + puntos >= 15) {
                puntosConductores[15].push_front(dni);
                info.puntos = 15;
                info.it = puntosConductores[15].begin();
            }
            else {
                int nuevos = info.puntos + puntos;
                puntosConductores[nuevos].push_front(dni);
                info.puntos = nuevos;
                info.it = puntosConductores[nuevos].begin();
            }
        }
        
    }

    int consultar(const string& dni) const {
        return buscar_conductor(dni).puntos;
    }

    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) throw
            domain_error("Puntos no validos");
        
        return (puntosConductores.count(puntos)) ? puntosConductores.at(puntos).size() : 0;
    }

    list<string> lista_por_puntos(int puntos) {
        if (puntos < 0 || puntos > 15) throw
            domain_error("Puntos no validos");
        
        return puntosConductores.at(puntos);
    }

private:
    struct InfoConductor {
        int puntos;
        list<string>::iterator it;
    };

    InfoConductor& buscar_conductor(const string& dni) {
        if (!conductores.count(dni)) throw
            domain_error("Conductor inexistente");
        
        return conductores[dni];
    }

    const InfoConductor& buscar_conductor(const string& dni) const{
        if (!conductores.count(dni)) throw
            domain_error("Conductor inexistente");
        
        return conductores.at(dni);
    }

    unordered_map<string, InfoConductor> conductores;
    unordered_map<int, list<string>> puntosConductores;
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    CarnetPuntos dgt;
    string dni;
    int puntos;
    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (opcion == "quitar") {
                cin >> dni >> puntos;
                dgt.quitar(dni, puntos);
            }
            else if (opcion == "recuperar") {
                cin >> dni >> puntos;
                dgt.recuperar(dni, puntos);
            }
            else if (opcion == "consultar") {
                cin >> dni;
                int puntosConductor = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << puntosConductor << "\n";
            }
            else if (opcion == "cuantos_con_puntos") {
                cin >> puntos;
                int cuantosPuntos = dgt.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay " << cuantosPuntos << "\n";
            }
            else if (opcion == "lista_por_puntos") {
                cin >> puntos;
                
                auto listaConductores = dgt.lista_por_puntos(puntos);
                cout << "Tienen " << puntos << ": ";
                for (auto const it : listaConductores) cout << it << " ";
                cout << "\n";
            }
        } catch (std::domain_error &exception) {
            cout << "ERROR: " << exception.what() << "\n";
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
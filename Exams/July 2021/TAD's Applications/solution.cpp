#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

class ElGrande {
private:
    struct InfoRegion {
        int mayoria;
        unordered_map<string, int> caballeros;
        unordered_set<string> jugadores;
        
        InfoRegion() : mayoria(0) { };
    };

    set<string> disputados;
    unordered_map<string, int> puntuaciones;
    unordered_map<string, InfoRegion> regiones;

public:

    void anyadir_jugador(const string& jugador) {
        if (puntuaciones.count(jugador)) throw
            domain_error("Jugador existente");
        
        puntuaciones[jugador] = 0;
    }

    void colocar_caballero(const string& jugador, const string& region) {
        if (!puntuaciones.count(jugador)) throw
            domain_error("Jugador no existente");
        
        InfoRegion& info = regiones[region];
        int& caballeros = info.caballeros[jugador];
        
        caballeros++;
        if (caballeros > info.mayoria) {
            if (info.jugadores.size() == 1)
                puntuaciones[*info.jugadores.begin()]--;
            
            info.jugadores.clear();
            info.jugadores.insert(jugador);
            info.mayoria = caballeros;

            puntuaciones[jugador]++;
            disputados.erase(region);
        }
        else if (caballeros == info.mayoria) {
            if (info.jugadores.size() == 1)
                puntuaciones[*info.jugadores.begin()]--;

            info.jugadores.insert(jugador);
            disputados.insert(region);
        }
    }

    int puntuacion(const string& jugador) const {
        return puntuaciones.at(jugador);
    }

    vector<string> regiones_en_disputa() {
        vector<string> list(disputados.size());
        copy(disputados.begin(), disputados.end(), list.begin());
        return list;
    }

    void expulsar_caballeros(const string& region) {
        if (!regiones.count(region) || regiones[region].mayoria == 0) throw
            domain_error("Region vacia");
        
        InfoRegion& info = regiones[region];
        if (info.jugadores.size() == 1)
            puntuaciones[*info.jugadores.begin()]--;
            
        regiones.erase(region);
        disputados.erase(region);
    }

};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    ElGrande juego;
    string jugador, region;
    while (opcion != "FIN") {
        try {
            if (opcion == "anyadir_jugador") {
                cin >> jugador;
                juego.anyadir_jugador(jugador);
            }
            else if (opcion == "colocar_caballero") {
                cin >> jugador >> region;
                juego.colocar_caballero(jugador, region);
            }
            else if (opcion == "puntuacion") {
                cin >> jugador;
                int puntuacion = juego.puntuacion(jugador);
                cout << "Puntuacion de " << jugador << ": " << puntuacion << "\n";
            }
            else if (opcion == "regiones_en_disputa") {
                vector<string> disputados = juego.regiones_en_disputa();

                cout << "Regiones en disputa: \n";
                for (auto elem : disputados) cout << elem << "\n";
            }
            else if (opcion == "expulsar_caballeros") {
                cin >> region;
                juego.expulsar_caballeros(region);
            }
        } catch(domain_error &exception) {
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
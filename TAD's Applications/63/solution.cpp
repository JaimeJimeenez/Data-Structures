#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map> 

using namespace std;

class Grande {
public:
    void anyadir_jugador(string jugador) {
        if (jugadores.count(jugador)) throw
            domain_error("Jugador existente");

        jugadores[jugador] = { };
    }

    void colocar_caballero(string jugador, string region) {
        InfoJugador& infoJugador = buscar_jugador(jugador);
        if (!regiones.count(region))
            regiones[region] = { };
        
        InfoRegion& infoRegion = buscar_region(region);
        infoJugador.caballeros_region[region]++;
        int caballeros = infoJugador.caballeros_region[region];

        if (infoRegion.ganador == "") {    

            infoRegion.ganador = jugador;
            infoRegion.caballeros_ganador = caballeros;

            infoJugador.puntuacion++;
        }
        else if (caballeros > infoRegion.caballeros_ganador && jugador != infoRegion.ganador) {
            string antiguo = infoRegion.ganador;
            jugadores[antiguo].puntuacion--;
            
            infoJugador.puntuacion++;
            infoRegion.caballeros_ganador = caballeros;
            infoRegion.ganador = jugador;
        }
        else if (caballeros == infoRegion.caballeros_ganador){
            string antiguo = infoRegion.ganador;
            jugadores[antiguo].puntuacion--;

            infoRegion.ganador = "";
        }
    }

    int puntuacion(string jugador) const {
        return buscar_jugador(jugador).puntuacion;
    }

    vector<string> regiones_en_disputa() {
        vector<string> disputados;

        auto it = regiones.begin();
        while (it != regiones.end()) {
            const InfoRegion& info = it->second;

            if (info.ganador == "") disputados.push_back(it->first);
            it++;
        }

        return disputados;
    }

    void expulsar_caballeros(string region) {
        InfoRegion& info = buscar_region(region);
        if (info.caballeros_ganador == 0) throw
            domain_error("Region vacia");
        
        string antiguo_ganador = info.ganador;

        jugadores[antiguo_ganador].puntuacion--;
        jugadores[antiguo_ganador].caballeros_region[region] = 0; 

        info.caballeros_ganador = 0;
        info.ganador = "";
    }

private:
    struct InfoRegion {
        string ganador;
        int caballeros_ganador;

        InfoRegion() : ganador(""), caballeros_ganador(0) { }
    };

    struct InfoJugador {
        int puntuacion;
        unordered_map<string, int> caballeros_region;

        InfoJugador() : puntuacion(0), caballeros_region() { }
    };

    unordered_map<string, InfoJugador> jugadores;
    map<string, InfoRegion> regiones;

    const InfoJugador& buscar_jugador(string jugador) const {
        auto it = jugadores.find(jugador);

        if (it == jugadores.end()) throw
            domain_error("Jugador no existente");
        return it->second;
    }

    InfoJugador& buscar_jugador(string jugador) {
        auto it = jugadores.find(jugador);

        if (it == jugadores.end()) throw
            domain_error("Jugador no existente");
        return it->second;
    }

    const InfoRegion& buscar_region(string region) const {
        auto it = regiones.find(region);

        if (it == regiones.end()) throw
            domain_error("Region vacia");
        return it->second;
    }

    InfoRegion& buscar_region(string region) {
        auto it = regiones.find(region);

        if (it == regiones.end()) throw
            domain_error("Region vacia");
        return it->second;
    }
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Grande juego;
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
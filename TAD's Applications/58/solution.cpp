#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {
public:

    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (estados.count(nombre)) throw
            domain_error("Estado ya existente");
        
        estados[nombre] = num_compromisarios;
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (!estados.count(nombre)) throw
            domain_error("Estado no encontrado");
        estados[estado].first[partido] += num_votos;
    }

    string ganador_en(const string& estado) const {
        if (!estados.count(estado)) throw
            domain_error("Estado no encontrado");
        
        string ganador;
        int maxVotos = 0;
        for (auto const& it : estados.at(estado).first) {
            if (it.second > maxVotos) {
                maxVotos = it.second;
                ganador = it.first;
            }
        }

        partidos
        return ganador;
    }

    vector<pair<string, int>> resultados() const {

    }

private:
    unordered_map<string, int> estados;
    map<string, unordered_map<string, int>> partidos;
};

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
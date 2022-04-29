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
        
        estados.insert( { nombre, { num_compromisarios }});
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        auto& info = buscar_estado(estado);

        info.num_votos[partido] += num_votos;
        if (info.ganador == "") {
            info.ganador = partido;
            info.num_votos_ganador = info.num_votos[partido];
            partidos[partido] += info.num_compromisarios;
        }
        else if (info.num_votos[partido] > info.num_votos_ganador) {
            string antiguo = info.ganador;

            info.ganador = partido;
            info.num_votos_ganador = info.num_votos[partido];

            partidos[antiguo] -= info.num_compromisarios;
            if (partidos[antiguo] == 0) partidos.erase(antiguo);
            partidos[partido] += info.num_compromisarios;
        }
    }

    string ganador_en(const string& estado) const {
        return buscar_estado(estado).ganador;
    }

    vector<pair<string, int>> resultados() const {
        return { partidos.begin(), partidos.end() };
    }

private:
   
   struct InfoEstado {
       InfoEstado(int num_compr) : num_compromisarios(num_compr), ganador(""), num_votos_ganador(-1), num_votos(0) { }
       
       int num_compromisarios;
       string ganador;
       int num_votos_ganador;
       unordered_map<string, int> num_votos;

   };

   map<string, int> partidos;
   unordered_map<string, InfoEstado> estados;

    InfoEstado& buscar_estado(const string& nombre) {
        auto it = estados.find(nombre);
        if (it == estados.end()) throw
            domain_error("Estado no encontrado");
        
        return it->second;
    }

    const InfoEstado& buscar_estado(const string& nombre) const {
        auto it = estados.find(nombre);
        if (it == estados.end()) throw
            domain_error("Estado no encontrado");
        
        return it->second;
    }
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    ConteoVotos elecciones;
    string nombre, estado;
    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo_estado") {
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            }
            else if (opcion == "sumar_votos") {
                int num_votos;
                cin >> estado >> nombre >> num_votos;
                elecciones.sumar_votos(estado, nombre, num_votos); 
            }
            else if (opcion == "ganador_en") {
                cin >> estado;
                const string& ganador = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (opcion == "resultados") {
                auto resultados = elecciones.resultados();

                for (auto elem : resultados) cout << elem.first << " " << elem.second << "\n";
            
            }

        } catch (std::domain_error &exception) {
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

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
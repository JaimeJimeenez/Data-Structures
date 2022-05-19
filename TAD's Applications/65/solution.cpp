#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

class Urgencias {
public:
    void nuevo_paciente(const string& paciente, int gravedad) {
        if (gravedad <= 0 || gravedad > 3) throw
            domain_error("Gravedad incorrecta");
        if (pacientes.count(paciente)) throw
            domain_error("Paciente repetido");

        auto it = listaEspera.at(gravedad - 1).insert(listaEspera.at(gravedad - 1).end(), paciente);
        pacientes[paciente] = { gravedad - 1, it };
    }

    int gravedad_actual(const string& paciente) const {
        const InfoPaciente& info = buscar_paciente(paciente);
        return info.gravedad; 
    }

    string siguiente() {
        
    }

    void mejora(const string& paciente) {

    }

    list<string> recuperados() {
        list<string> lista;

        auto it = listRecuperados.begin();
        while (it != listRecuperados.end()) {
            lista.push_back(*it);
            it++;
        }

        return lista;
    }

private:
    vector<list<string>> listaEspera{ 3 };
    set<string> listRecuperados;

    struct InfoPaciente {
        int gravedad;
        list<string>::iterator it;

        InfoPaciente(int gravedad, list<string>::iterator it) : gravedad(gravedad), it(it) { }
    };

    unordered_map<string, InfoPaciente> pacientes;

    const InfoPaciente& buscar_paciente(const string& paciente) const {
        auto it = pacientes.find(paciente);
        if (it == pacientes.end()) throw
            domain_error("Paciente inexistente");

        return it->second;
    }
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Urgencias urgencias;

    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo_paciente") {

            }
            else if (opcion == "gravedad_actual") {

            }
            else if (opcion == "siguiente") {

            }
            else if (opcion == "mejora") {

            }
            else if (opcion == "recuperados") {
                list<string> recuperados = urgencias.recuperados();
                auto it = recuperados.begin();

                while (it != recuperados.end()) {
                    cout << *it << endl;
                    it++;
                }
            }
        } catch (domain_error &exception) {
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
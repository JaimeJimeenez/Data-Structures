#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <list>

using namespace std;

class Medicos {
public:
    void altaMdedico(const string& medico) {
        if (medicos.count(medico)) throw
            domain_error("Medico existente");
        
        medicos[medico] = { };
    }

    void pedirConsulta(const string& paciente, const string& medico) {
        if (!medicos.count(medico)) throw
            domain_error("Medico inexistente");

        if (pacientes.count(paciente) && pacientes[paciente].consulta.count(medico)) throw
            domain_error("Paciente ya esperando");
        
        auto it = medicos[medico].listaPacientes.insert(medicos[medico].listaPacientes.end(), paciente);
        InfoPaciente& info = pacientes[paciente];
        info.consulta.insert( { medico, it } );
    }

    string siguientePaciente(const string& medico) const {
        InfoMedico info = buscar_medico(medico);
        return info.listaPacientes.front();
    }

    void atenderConsulta(const string& medico) {
        InfoMedico& info = buscar_medico(medico);
        string paciente = info.listaPacientes.front();

        info.listaPacientes.pop_front();
        pacientes[paciente].consulta.erase(medico);
    }

    list<string> abandonarConsulta(const string& paciente) {
        if (!pacientes.count(paciente)) throw
            domain_error("Paciente inexistente");
        
        list<string> lista;
        InfoPaciente info = pacientes[paciente];
        for (auto it : info.consulta) {
            medicos[it.first].listaPacientes.erase(it.second);
            lista.push_back(it.first);
        } 
            
        return lista;
    }

private:

    struct InfoPaciente {
        map<string, list<string>::iterator> consulta;
    };

    struct InfoMedico {
        list<string> listaPacientes;
    };

    unordered_map<string, InfoMedico> medicos;
    unordered_map<string, InfoPaciente> pacientes;

    const InfoMedico& buscar_medico(const string& medico) const {
        auto it = medicos.find(medico);
        if (it == medicos.end()) throw
            domain_error("Medico inexistente");
        if (it->second.listaPacientes.empty()) throw
            domain_error("Medico sin pacientes");

        return it->second;
    }

    InfoMedico& buscar_medico(const string& medico) {
        auto it = medicos.find(medico);
        if (it == medicos.end()) throw
            domain_error("Medico inexistente");
        if (it->second.listaPacientes.empty()) throw
            domain_error("Medico sin pacientes");

        return it->second;
    } 
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Medicos consultas;
    string medico, paciente;
    while (opcion != "FIN") {
        try {

            if (opcion == "altaMedico") {
                cin >> medico;
                consultas.altaMdedico(medico);
            }
            else if (opcion == "pedirConsulta") {
                cin >> paciente >> medico;
                consultas.pedirConsulta(paciente, medico);
            }
            else if (opcion == "siguientePaciente") {
                cin >> medico;
                paciente = consultas.siguientePaciente(medico);

                cout << paciente << "\n";
            }
            else if (opcion == "atenderConsulta") {
                cin >> medico;
                consultas.atenderConsulta(medico);
            }
            else if (opcion == "abandonarConsulta") {
                cin >> paciente;
                list<string> abandonados = consultas.abandonarConsulta(paciente);

                cout << "Medicos abandonados: ";
                for (auto elem : abandonados) cout << elem << " ";
                cout << "\n";
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
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

class Urgencias {
public:

  Urgencias() : sala(3) { };

  void nuevo_paciente(const string& paciente, int gravedad) {
    if (pacientes.count(paciente)) throw
      domain_error("Paciente repetido");
    if (gravedad < 1 || gravedad > 3) throw
      domain_error("Gravedad incorrecta");
    
    auto it = sala[gravedad - 1].insert(sala[gravedad - 1].end(), paciente);
    pacientes[paciente] = { gravedad, it };
  }

  int gravedad_actual(const string& paciente) const {
    return buscar_paciente(paciente).gravedad;
  }

  string siguiente() {

    for (int i = 2; i >= 0; i--) {
      if (!sala[i].empty()) {
        string paciente = sala[i].front();
        
        sala[i].pop_front();
        pacientes.erase(paciente);

        return paciente;
      }
    }

    throw domain_error("No hay pacientes");
  }

  void mejora(const string& paciente) {
    InfoPaciente& info = buscar_paciente(paciente);

    if (info.gravedad == 1) {
      sala[info.gravedad - 1].erase(info.it);
      pacientes.erase(paciente);
      sanos.insert(paciente);
    }
    else {
      sala[info.gravedad - 1].erase(info.it);
      info.gravedad--;
      info.it = sala[info.gravedad - 1].insert(sala[info.gravedad - 1].begin(), paciente);
    }
  }

  list<string> recuperados() {
    list<string> lista;

    for (auto paciente : sanos)
      lista.push_back(paciente);

    return lista;
  }

private:
  
  struct InfoPaciente {
    int gravedad;
    list<string>::iterator it;
  };

  unordered_map<string, InfoPaciente> pacientes;
  vector<list<string>> sala;
  set<string> sanos;
  
  const InfoPaciente& buscar_paciente(const string& paciente) const {
    auto it = pacientes.find(paciente);
    if (it == pacientes.end()) throw
      domain_error("Paciente inexistente");
    
    return it->second;
  }

  InfoPaciente& buscar_paciente(const string& paciente) {
    auto it = pacientes.find(paciente);
    if (it == pacientes.end()) throw
      domain_error("Paciente inexsitente");

    return it->second;
  }
};

bool tratar_caso() {
  string opcion;
  cin >> opcion;
  if (!cin) return false;

  Urgencias urgencias;
  string paciente;
  while (opcion != "FIN") {
    try {
      if (opcion == "nuevo_paciente") {
        int gravedad;
        cin >> paciente >> gravedad;
        urgencias.nuevo_paciente(paciente, gravedad);
      }
      else if (opcion == "gravedad_actual") {
        cin >> paciente;
        int gravedad = urgencias.gravedad_actual(paciente);

        cout << "La gravedad de " << paciente << " es " << gravedad << "\n";
      }
      else if (opcion == "siguiente") {
        string siguiente = urgencias.siguiente();

        cout << "Siguiente paciente: " << siguiente << "\n";
      }
      else if (opcion == "mejora") {
        cin >> paciente;
        urgencias.mejora(paciente);
      }
      else if (opcion == "recuperados") {
        list<string> sanos = urgencias.recuperados();

        cout << "Lista de recuperados: ";
        for (auto paciente : sanos) cout << paciente << " ";
        cout << "\n";
      }
    } catch(domain_error &exception) {
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
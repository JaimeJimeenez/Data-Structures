#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

class OficinaEmpleo {
public:
  void altaOficina(const string& nombre, const string& empleo) {
    empleos[empleo].push_back(nombre);
    if (!personas.count(nombre)) personas[nombre].insert( { empleo, --empleos[empleo].end() } );
    else if (!personas[nombre].count(empleo)) personas[nombre].insert( { empleo, --empleos[empleo].end() } );
  }

  string ofertaEmpleo(const string& empleo) {
    if (!empleos.count(empleo)) throw
      domain_error("No existen personas apuntadas a este empleo");
    
    string cualificada = empleos[empleo].front();
    personas[cualificada].erase(empleo);
    empleos[empleo].pop_front();

    auto empleosCualificada = personas[cualificada];
    auto it = empleosCualificada.begin();
    
    while (it != --empleosCualificada.end()) {
      cout << it->first << endl;
      empleos[it->first].erase(it->second);
      it++;
    }

    if (empleos.empty()) empleos.erase(empleo);
    personas.erase(cualificada);

    return cualificada;
  }

  vector<string> listadoEmpleos(const string& persona) const {
    if (!personas.count(persona)) throw 
      domain_error("Persona inexistente");
    return { };
  }

private:
  unordered_map<string, list<string>> empleos;
  unordered_map<string, map<string, list<string>::iterator>> personas;
};

bool tratar_caso() {
  string opcion;
  cin >> opcion;
  if (!cin) return false;

  OficinaEmpleo oficina;
  string empleo, persona;
  while (opcion != "FIN") {
    try {
      //cout << opcion << endl;
      if (opcion == "altaOficina") {
        cin >> persona >> empleo;
        oficina.altaOficina(persona, empleo);
      }
      else if (opcion == "ofertaEmpleo") {
        cin >> empleo;
        
        string cualificada = oficina.ofertaEmpleo(empleo);
        cout << empleo << ": " << cualificada << "\n";
      }
      else if (opcion == "listadoEmpleos") {
        cin >> persona;
        vector<string> empleos = oficina.listadoEmpleos(persona);

        cout << persona << ": ";
        for (auto empleo : empleos) 
          cout << empleo << " ";
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
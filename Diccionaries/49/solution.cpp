#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "MapTree.h"

using namespace std;

void actualizados(vector<string> const &actualizacion) {
  for (auto elem : actualizacion)
    cout << elem << " ";
  cout << endl;
}

void actualizacion(MapTree<string, int>& nuevo, MapTree<string, int>& viejo) {
  vector<string> eliminados, modificados;

  for (auto& it : viejo)
    if (!nuevo.contains(it.key)) eliminados.push_back(it.key);
    else{
      if (it.value != nuevo[it.key]) modificados.push_back(it.key);
      nuevo.erase(it.key);
    }

  if (eliminados.empty() && nuevo.empty() && modificados.empty())
    cout << "Sin cambios\n";
  else if (!nuevo.empty()) {
    cout << "+ ";
    for (auto const& it : nuevo)
      cout << it.key << " ";
    cout << endl;
  }
  if (!eliminados.empty()) {
    cout << "- ";
    actualizados(eliminados);
  }
  if (!modificados.empty()) {
    cout << "* ";
    actualizados(modificados);
  }
}

void tratar_caso() {
  string linea, palabra;
  getline(cin, linea);
  
  MapTree<string, int> viejoDiccionario;
  stringstream viejo(linea);
  while (viejo >> palabra) 
    viejo >> viejoDiccionario[palabra];
  
  getline(cin, linea);

  MapTree<string, int> nuevoDiccionario;
  stringstream nuevo(linea);
  while (nuevo >> palabra) 
    nuevo >> nuevoDiccionario[palabra];

  actualizacion(nuevoDiccionario, viejoDiccionario);
  cout << "---\n";
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  int num_casos;
  cin >> num_casos;
  cin.ignore();
  
  while (num_casos--) { tratar_caso(); }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
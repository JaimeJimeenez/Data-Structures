#include <iostream>
#include <fstream>
#include <string> 
#include <list>
#include <unordered_map>
#include <set>

using namespace std;

class VentaLibros {
public:

  void nuevoLibro(const string& nombre, int ejemplares) {
    libros[nombre] += ejemplares;
  }

  void comprar(const string& nombre) {

  }

  bool estaLibro(const string& nombre) const {

  }

  void elimLibro(const string& nombre) {

  }

  int numEjemplares(const string& nombre) {

  }

  list<string> top10() {

  }
    
private:

  unordered_map<string, int> libros;
  struct InfoLibro {
    InfoLibro(int ejemplares) : ejemplares(ejemplares), vendidos(0) { }

    int vendidos, ejemplares;
    set<int>::iterator;
  };

  set<InfoLibro> vendidos;
};

bool tratar_caso() {
  int N;
  cin >> N;
  if (!cin) return false;
  
  VentaLibros venta;
  string opcion, nombre;
  int ejemplares;
  while (N--) {
    cin >> opcion;
    if (opcion == "nuevoLibro") {
      cin >> ejemplares;
      getline(cin, nombre);
      venta.nuevoLibro(nombre, ejemplares);
    }
    else if (opcion == "comprar") {
      getline(cin, nombre);
      venta.comprar(nombre);
    }
    else if (opcion == "estaLibro") {
      getline(cin, nombre);
      if (venta.estaLibro(nombre))
        cout << "El libro " << nombre << "esta en el sistema\n";
      else
        cout << "No existe el libro " << nombre << " en el sistema\n"; 
    }
    else if (opcion == "numEjemplares") {
      getline(cin, nombre);

      int numEjemplares = venta.numEjemplares(nombre);
      if (numEjemplares > 0) cout << "Existe " << numEjemplares << " ejemplares del libro " << nombre << "\n";
      else cout << "No existe el libro " << nombre << " en el sistema\n";
    }
    else if (opcion == "top10") {

    }
  }

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
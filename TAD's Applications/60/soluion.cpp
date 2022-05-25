#include <iostream>
#include <fstream>
#include <string> 
#include <list>
#include <unordered_map>
#include <set>

using namespace std;

class VentaLibros {
public:

  void nuevoLibro(int ejemplares, const string& libro) {
    libros[libro].ejemplares += ejemplares;
  }

  void comprar(const string& libro) {
    if (!libros.count(libro)) throw
      invalid_argument("Libro no existente");
    if (libros[libro].ejemplares == 0) throw 
      out_of_range("No hay ejemplares");
    
    libros[libro].ejemplares--;
    libros[libro].vendidos++;
  }

  bool estaLibro(const string& libro) const {
    return libros.count(libro);
  }

  void elimLibro(const string& libro) {

  }

  int numEjemplares(const string& libro) {
    return 0;
  }

  list<string> top10() {
    return { };
  }
    
private:

  struct InfoLibro {
    int ejemplares;
    int vendidos;
  };

  unordered_map<string, InfoLibro> libros;

};

bool tratar_caso() {
  int N;
  cin >> N;
  if (!cin) return false;
  
  VentaLibros venta;
  string opcion, libro;
  int ejemplares;
  while (N--) {
    cin >> opcion;
    try {
      if (opcion == "nuevoLibro") {
        cin >> ejemplares;
        getline(cin, libro);
        venta.nuevoLibro(ejemplares, libro);
      }
      else if (opcion == "comprar") {
        getline(cin, libro);
        venta.comprar(libro);
      }
      else if (opcion == "estaLibro") {
        getline(cin, libro);
        if (venta.estaLibro(libro))
          cout << "El libro " << libro << " esta en el sistema\n";
        else
          cout << "No existe el libro " << libro << " en el sistema\n"; 
    }
      else if (opcion == "numEjemplares") {
        getline(cin, libro);

        int numEjemplares = venta.numEjemplares(libro);
        if (numEjemplares > 0) cout << "Existe " << numEjemplares << " ejemplares del libro " << libro << "\n";
        else cout << "No existe el libro " << libro << " en el sistema\n";
    }
    else if (opcion == "top10") {

      }
    } catch (domain_error& exception) {
      cout << "ERROR: " << exception.what() << "\n";
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
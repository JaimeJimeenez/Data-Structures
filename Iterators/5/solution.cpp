/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no se tendrá en cuenta para la corrección.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */
 
//@ <answer>
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1:
  Componente 2:
*/
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>
#include <string>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
  Categoria categoria;
  string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream &operator<<(ostream &out, const Plato &plato) {
  switch (plato.categoria) {
    case Categoria::Primero:
      out << "1";
      break;
    case Categoria::Segundo:
      out << "2";
      break;
    case Categoria::Postre:
      out << "P";
      break;
  }
  out << " " << plato.nombre;
  return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------



void print(const list<Plato> & platos) {
  
  for (auto it = platos.begin(); it != platos.end(); ++it) 
    cout << *it << endl;

  cout << "---\n";
}

//erase() devuelve un iterador que apunta al siguiente de la lista

// Indica el coste en función del tamaño del parámetro de entrada
void ordenar_menu(list<Plato> &platos) {
  auto itPrimero = platos.begin();
  auto itSegundo = itPrimero;
  auto it = platos.begin();

  while (it != platos.end() && it->categoria != Categoria::Postre) {
    auto itAux = it;
    if (it->categoria == Categoria::Primero) {
      itPrimero = platos.insert(platos.begin(), *it);
      itAux = platos.erase(it);
      it = itAux;
    }
    else if (it->categoria == Categoria::Segundo) {
      itSegundo = platos.insert(itSegundo, *it);
      itAux = platos.erase(it);
      it = itAux;
    }
  }

  print(platos);
}

bool tratar_caso() {
  int N;
  cin >> N;
  if (N == 0)
    return false;
  
  list<Plato> menu;
  char categoria;
  string nombre;
  
  while (N--) {
    cin >> categoria;
    getline(cin, nombre);

    switch(categoria) {
      case '1':
        menu.push_front({Categoria::Primero, nombre});
        break;
      case '2':
        menu.push_front({Categoria::Segundo, nombre});
        break;
      case 'P':
        menu.push_back({Categoria::Postre, nombre});
        break;
    }
  }

  ordenar_menu(menu);
  return true;
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}


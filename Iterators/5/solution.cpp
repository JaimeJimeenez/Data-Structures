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

    Componente 1: Jaime Jiménez Nieto
    Componente 2: Iván Pisonero Díaz
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <string>
#include <list>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream& operator<<(ostream& out, const Plato& plato) {
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


// Coste lineal con respecto a platos.size()
void ordenar_menu(list<Plato>& platos) {
    auto it = platos.begin(); 
    auto it2 = platos.begin(); //Apuntará a la posición posterior al último primero procesado
    int size = platos.size();
    Plato aux;

    for (int i = 0; i < size; i++) {
        if (it->categoria == Categoria::Primero) {
            it2 = platos.insert(it2, *it);
            aux = *it;
            it = platos.erase(it);

            if (it2 != platos.end()) {
                it2++;
            }
            
            if (it->categoria == aux.categoria && it->nombre == aux.nombre) {
                it = it2;
            }
        }
        else if (it->categoria == Categoria::Postre) {
            platos.push_back(*it);

            if (it == it2 && it != platos.end()) {
                it2++;
            }
            it = platos.erase(it);
        }
        else {
            ++it;
        }
    }

}

Categoria charACat(char c) {
    Categoria res;
    switch (c) {
    case 'P':
        res = Categoria::Postre;
        break;
    case '1':
        res = Categoria::Primero;
        break;
    case '2':
        res = Categoria::Segundo;
        break;
    }
    return res;
}


bool tratar_caso() {
    int N;
    cin >> N;
    if (N == 0) { return false; }

    list<Plato> platos;
    char cat;
    string nombre;

    while (N > 0) {
        cin >> cat;
        getline(cin, nombre);
        platos.push_back({ charACat(cat) , nombre });
        N--;
    }

    ordenar_menu(platos);

    for (Plato p : platos) {
        cout << p << '\n';
    }
    cout << "---" << '\n';
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

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}
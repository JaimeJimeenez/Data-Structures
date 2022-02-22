/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Jaime Jiménez Nieto
  Componente 2: Iván Pisonero Díaz
  */

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ELEMS = 2000;
 
class Multiconjunto {
public:

    //Coste constante
    Multiconjunto() : num_elems(0) { }   

    //Coste lineal con respecto a num_elems
    void anyadir(int elem) {
        int pos = busqueda_binaria(0, num_elems, elem);

        if (pos == num_elems || elem != elems[pos].valor) {
            for (int i = num_elems; i > pos; i--) {
                elems[i] = elems[i - 1];
            }
            num_elems++;
            elems[pos] = { elem, 1 };
        }
        else if (elems[pos].valor == elem)
            elems[pos].multiplicidad++;
        
    }

    //Coste logarítmico con respecto a num_elems
    void eliminar(int elem) {
        int pos = busqueda_binaria(0, num_elems, elem);
        
        if (pos < num_elems && elems[pos].valor == elem) {
            elems[pos].multiplicidad--;
            
            if (elems[pos].multiplicidad == 0) {
                for (int i = pos; i < num_elems - 1; i++) {
                    elems[i] = elems[i + 1];
                }
                num_elems--;
            }
            
        }
    }

    //Coste logarítmico con respecto a num_elems
    bool pertenece(int elem) const {
        int pos = busqueda_binaria(0, num_elems, elem);
        return pos < num_elems&& elems[pos].valor == elem && elems[pos].multiplicidad != 0;
    }

private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;

    //Coste logarítmico con respecto a (fin - ini)
    int busqueda_binaria(int ini, int fin, int elem) const {

        int mitad = (ini + fin) / 2;

        if (fin == ini) {
            return ini;
        }
        else if ((elem > elems[mitad].valor) && (fin - 2 <= ini)) {
            return fin;
        }
        else if ((elem <= elems[mitad].valor) && (fin - 1 == ini)) {
            return ini;
        }
        else if (elem > elems[mitad].valor) {
            return busqueda_binaria(mitad + 1, fin, elem);
        }
        else {
            return busqueda_binaria(ini, mitad, elem);
        }
    }
};


// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
//Coste lineal con respecto a M
bool tratar_caso() {

    int M;
    cin >> M;
    if (M == 0)
        return false;

    Multiconjunto conjunto;
    vector<int> elementosConjunto(M);
    vector<int> secuencia(M);
    string solucion;

    for (int i = 0; i < M; i++) {
        cin >> elementosConjunto[i];
        conjunto.anyadir(elementosConjunto[i]);
    }

    for (int i = 0; i < M; i++) {
        cin >> secuencia[i];
    }

    for (int i = 0; i < M; i++) {
        if (elementosConjunto[i] == secuencia[i]) {
            solucion.push_back('#');
            conjunto.eliminar(secuencia[i]);
        }
        else
            solucion.push_back('.');
    }

    for (int i = 0; i < M; i++) {
        if (conjunto.pertenece(secuencia[i]) && solucion[i] != '#') {
            solucion[i] = 'O';
            conjunto.eliminar(secuencia[i]);
        }
    }

    cout << solucion << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    system("PAUSE");
#endif
    return 0;
}
///*
// * ---------------------------------------------------
// *                ESTRUCTURAS DE DATOS
// * ---------------------------------------------------
// *              Manuel Montenegro Montes
// *              Facultad de Informática
// *         Universidad Complutense de Madrid
// * ---------------------------------------------------
// */
//
// /*
//  *  componentes del grupo:
//  *
//  * Estudiante 1: Roxanne Caiafa
//  * Estudiante 2: Jaime Jiménez
//  *
//  */
//
#include <iostream>
#include <cassert>
#include <fstream>
//
const int GRADO_MAX = 10000;
//  /* Define la clase 'Polinomio' aquí */
class Polinomio {
	public:
		Polinomio(); // constructora
		void anyadir_monomio(int coef,int exp); //modificadora
		long evaluar(int valor) const;//observadora
	private:
		int coeficientes[GRADO_MAX + 1]{};//{} inicializa todo el array a 0;
		int gradoMayor;

};
///*
//O(n) siendo n el numero de elementos que se pueden guardar en el array
//*/
Polinomio::Polinomio() {
	
	this->gradoMayor = 0;
}

///*
//por defecto todo el array está inicializado a 0 
//por lo que si un elemento de los coeficientes es distinto a 0 
//dicho valor será sumado  con el nuevo coeficiente que se quiere asignar.
//pero como se garantiza que siempre habrá un 0 es decir, un numero neutro,
//esto no afecta al resultado de sumar
//3x^2+4x^2 = 7x^2
//O(1);
//*/
void Polinomio::anyadir_monomio(int coef, int exp) {
	assert(exp <= GRADO_MAX && exp >= 0 );
		this->coeficientes[exp] += coef;
}
///*
//Como no hay forma de saber hasta dónde evaluar el array de coeficientes,
//o cuáles evaluar,se debe recorrer todo el array .
//O(n) siendo n el grado mayor que hay en el array
//*/
long Polinomio::evaluar(int valor) const {
	long result = 0;
	long exp = valor;
	for (int i = 0; i < GRADO_MAX; i++) {
		if (coeficientes[i] != 0) {
			if (i == 0) result += coeficientes[i];
			else result += coeficientes[i] * exp;
		}
		if (i > 0) {
			exp *= valor;
	
		}
	}
	return result;
}

bool tratar_caso() {
    
	int monomios, valor;
	std::cin >> monomios >> valor;
	if (monomios == 0 && valor == 0) return false;
	
	int i = 0, coef,exp;
	Polinomio poli;
	while (i < monomios) {
		std::cin >> coef >> exp;
		poli.anyadir_monomio(coef,exp);
		++i;
	}
	std::cout << poli.evaluar(valor) << '\n';
	return true;

}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("l1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
//	system("PAUSE");
#endif
	return 0;
}
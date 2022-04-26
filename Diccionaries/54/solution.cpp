#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

void calificaciones(const map<string, map<string, string>> &preguntas, map<string, int> &estudiantes, int numPreguntas) {
    string pregunta, respuesta;
    
    while (numPreguntas--) {
        cin >> pregunta >> respuesta;
        if (preguntas.count(pregunta) == 1) {
            auto respuestas = preguntas.at(pregunta);
            for (auto const& it : respuestas) 
                if (it.second == respuesta) estudiantes[it.first]--;
        }
    }

}

void estudiantesPerfectos(const map<string, int>& estudiantes) {
    int perfectos = 0;
    
    for (auto const& estudiante : estudiantes)
        if (estudiante.second == 0) perfectos++;
    cout << perfectos << endl; 

}

bool tratar_caso() {
    int N, A, P;
    cin >> N >> A >> P;
    if (N == 0 && A == 0 && P == 0) return false;

    map<string, map<string, string>> preguntas;
    map<string, int> estudiantes;
    while (N--) {
        string nombre;
        cin >> nombre;
        for (int i = 0; i < A; i++) {
            string pregunta, respuesta;
            cin >> pregunta >> respuesta;
            preguntas[pregunta].insert( { nombre, respuesta } );
        }
        estudiantes[nombre] = A;
    }

    calificaciones(preguntas, estudiantes, P);
    estudiantesPerfectos(estudiantes);
    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso());

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
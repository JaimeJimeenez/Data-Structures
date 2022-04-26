#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Autoescuela {
public:

    void alta(const string& alumno, const string& profesor) {
        if (alumnos.count(alumno)) {
            string antiguo = alumnos.at(alumno).profesor;
            profesores.at(antiguo).erase(alumno);
        }

        profesores[profesor].insert(alumno);
        alumnos[alumno].profesor = profesor;
    }

    bool es_alumno(const string& alumno, const string& profesor) const {
        return alumnos.count(alumno) && alumnos.at(alumno).profesor == profesor;
    }

    int puntuacion(const string& alumno) const {
        return buscarAlumno(alumno).puntuacion;
    }

    void actualizar(const string& alumno, int puntuacion) {
        buscarAlumno(alumno).puntuacion += puntuacion;
    }

    vector<string> examen(const string& profesor, int pMinima) const {
        vector<string> examinados;
        if (!profesores.count(profesor)) return examinados;

        for (const string& alumno : profesores.at(profesor))
            if (alumnos.at(alumno).puntuacion >= pMinima) examinados.push_back(alumno);
        
        return examinados;
    }

    void aprobar(const string alumno) {
        profesores[buscarAlumno(alumno).profesor].erase(alumno);
        alumnos.erase(alumno);
    }

    void print() {
        for (auto const& it : alumnos)
            cout << it.first << " " << it.second.profesor << "\n";
    }

private:
    
    struct InfoAlumno {
        InfoAlumno() : profesor(""), puntuacion(0) { }
        string profesor;
        int puntuacion;
        
    };

    unordered_map<string, InfoAlumno> alumnos;

    const InfoAlumno &buscarAlumno(const string& alumno) const {
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) throw
            std::domain_error("El alumno " + alumno + " no esta matriculado");
        
        return it->second;
    }

    InfoAlumno& buscarAlumno(const string& alumno) {
        auto it = alumnos.find(alumno);
        if (it == alumnos.end()) throw
            std::domain_error("El alumno " + alumno + " no esta matriculado");
        
        return it->second;
    }

    unordered_map<string, set<string>> profesores;
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    Autoescuela autoescuela;
    string alumno, profesor;
    int puntuacion;

    while (opcion != "FIN") {
        try {
            if (opcion == "alta") {
                cin >> alumno >> profesor;
                autoescuela.alta(alumno, profesor);
            }
            else if (opcion == "es_alumno") {
                cin >> alumno >> profesor;
                if (autoescuela.es_alumno(alumno, profesor)) cout << alumno + " es alumno de " << profesor << "\n";
                else cout << alumno << " no es alumno de " << profesor << "\n";
            }
            else if (opcion == "puntuacion") {
                cin >> alumno;
                int pAlumno = autoescuela.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << pAlumno << "\n";
            }
            else if (opcion == "actualizar") {
                cin >> alumno >> puntuacion;
                autoescuela.actualizar(alumno, puntuacion);
            }
            else if (opcion == "examen") {
                cin >> profesor >> puntuacion;

                cout << "Alumnos de " << profesor << " a examen:\n";
                auto alumnosExamen = autoescuela.examen(profesor, puntuacion);
                for (auto elem : alumnosExamen)
                    cout << elem << "\n";
            }
            else if (opcion == "aprobar") {
                cin >> alumno;
                autoescuela.aprobar(alumno);
            }
        } catch (std::domain_error &exception) {
            cout << "ERROR\n";
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
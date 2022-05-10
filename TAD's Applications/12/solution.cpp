/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
  Utiliza las librerías de la STL en esta práctica.
  
  No te olvides del coste de las operaciones
*/
 
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Jaime Jiménez Nieto
  Componente 2: Ivan Pisonero Diaz
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <list>
#include <set>


using namespace std;

class Spitter {
public:

  //O(N) siendo N el número de hashtags
  void nueva_publicacion(int id, const string& texto, const vector<string> &hashtags) {
    if (publicaciones.count(id))
      throw std::domain_error("Identificador duplicado");
      
    recientes.push_front(texto);
    publicaciones.insert( { id, { { texto, recientes.begin() }, { } } } );
      
    auto& pHashtags = publicaciones[id].second;
    for (auto hashtag : hashtags) {
      pHashtags.insert(hashtag);
      populares[hashtag]++;
    }
  }

  //O(N) siendo N el número de hashtags 
  void borrar_publicacion(int id) {
    if (publicaciones.count(id)) {
      auto it = publicaciones[id].first.second;
      recientes.erase(it);

      auto pHashtags = publicaciones[id].second;
      for (auto hashtag : pHashtags) populares[hashtag]--;
      publicaciones.erase(id);
    }  
  }

  //O(N) siendo N el número pasado como parámetro
  vector<string> mas_recientes(int n) const {
    auto it = recientes.begin();
    vector<string> ultimas;

    while (it != recientes.end() && n--) {
      ultimas.push_back(*it);
      it++;
    }
    return ultimas;
  }

  //O(N) siendo N el número de hashtags
  vector<string> hashtags(int id) const {
    if (publicaciones.count(id) == 0)
      throw std::domain_error("Publicacion no existente");
      
    auto pHashtags = publicaciones.at(id).second;
    vector<string> vHashtags;
    for (auto elem : pHashtags) vHashtags.push_back(elem);

    return vHashtags;
  }

  //O(1)
  void anyadir_hashtag(int id, const string &hashtag) {
    if (publicaciones.count(id) == 0)
      throw std::domain_error("Publicacion no existente");

    auto& pHashtags = publicaciones[id].second;
    if (pHashtags.count(hashtag) == 0) {
      pHashtags.insert(hashtag);
      populares[hashtag]++;
    }  
  }

  //O(1)
  int popularidad(const string &hashtag) const {
    if (populares.count(hashtag)) return populares.at(hashtag);
    return 0;
  }

private:
  list<string> recientes;
  unordered_map<int, pair<pair<string, list<string>::iterator>, set<string>>> publicaciones;
  unordered_map<string, int> populares;
};

bool tratar_caso() {
  string opcion;
  cin >> opcion;
  if (!cin) return false;

  Spitter spitter;
  string texto;
  int id;
  while (opcion != "FIN") {
    try {
      if (opcion == "nueva_publicacion") {
        vector<string> hashtags; 
        string palabra, linea;
                
        cin >> id;
        getline(cin, texto);
        getline(cin, linea);

        stringstream flujo(linea);
        while (flujo >> palabra) hashtags.push_back(palabra);
        spitter.nueva_publicacion(id, texto, hashtags);
      }
      if (opcion == "borrar_publicacion") {
        cin >> id;
        spitter.borrar_publicacion(id);
      }
      if (opcion == "mas_recientes") {
        int nRecientes;
        cin >> nRecientes;
        auto recientes = spitter.mas_recientes(nRecientes);                
        
        cout << "Las " << recientes.size() << " publicaciones mas recientes:\n";
        for (auto elem : recientes) cout << elem << "\n";
      }
      if (opcion == "hashtags") {
        cin >> id;
                
        auto hashtags = spitter.hashtags(id);
        for (auto elem : hashtags) cout << elem << " ";
        cout << endl;
      }
      if (opcion == "anyadir_hashtag") {
        cin >> id >> texto;
        spitter.anyadir_hashtag(id, texto);
      }
      if (opcion == "popularidad") {
        cin >> texto;
        cout << spitter.popularidad(texto) << "\n";
      }
    } catch (std::domain_error& exception) {
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


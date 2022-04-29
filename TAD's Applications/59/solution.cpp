#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class iPud {
public:
    void addSong(const string& cancion, const string& artista, int duracion) {
        if (ipud.count(cancion)) throw
            domain_error("ERROR addSong");
        
        ipud[cancion] = { artista, duracion, escuchadas.end(), playlist.end() };
    }

    void addToPlaylist(const string& cancion) {
        if (!ipud.count(cancion)) throw
            domain_error("ERROR addToPlaylist");

        if (ipud[cancion].playlist == playlist.end()) {
            ipud[cancion].playlist = playlist.insert(playlist.end(), cancion);
            duracionPlaylist += ipud[cancion].duracion;
        }
        
    }

    int totalTime() {
        return (playlist.empty()) ? 0 : duracionPlaylist;
    }

    string current() const {
        if (playlist.empty()) throw
            domain_error("ERROR current");
        
        return playlist.front();
    }

    string play() {
        if (!playlist.empty()) {
            string cancion = playlist.front();
            playlist.pop_front();

            if (ipud[cancion].recientes != escuchadas.end())
                escuchadas.erase(ipud[cancion].recientes);
            
            ipud[cancion].recientes = escuchadas.insert(escuchadas.begin(), cancion);
            duracionPlaylist -= ipud[cancion].duracion;
            ipud[cancion].playlist = playlist.end();

            return cancion;
        }

        throw domain_error ("No hay canciones en la lista");
    }

    vector<string> recent(int n) {
        vector<string> recientes;
        auto it = escuchadas.begin();

        while (it != escuchadas.end() && n--) {
            recientes.push_back(*it);
            ++it;
        }

        return recientes;
    }

    void deleteSong(const string& cancion) {
        if (ipud.count(cancion)) {

            InfoCancion& info = ipud[cancion];

            if (!playlist.empty() && info.playlist != playlist.end()) {
                duracionPlaylist = duracionPlaylist - info.duracion;
                playlist.erase(info.playlist);
            }

            if (!escuchadas.empty() && info.recientes != escuchadas.end()) 
                escuchadas.erase(info.recientes);

            ipud.erase(cancion);
        }
    }

private:
    int duracionPlaylist = 0;

    list<string> playlist;
    list<string> escuchadas;

    struct InfoCancion {
        string artista;
        int duracion;
        list<string>::iterator recientes;
        list<string>::iterator playlist;
    };

    unordered_map<string, InfoCancion> ipud;
};

bool tratar_caso() {
    string opcion;
    cin >> opcion;
    if (!cin) return false;

    iPud reproductor;
    string artista, cancion;
    while (opcion != "FIN") {
        try {

            if (opcion == "addSong") {
                int duracion;
                cin >> cancion >> artista >> duracion;
                reproductor.addSong(cancion, artista, duracion);
            }
            else if (opcion == "addToPlaylist") {
                cin >> cancion;
                reproductor.addToPlaylist(cancion);
            }
            else if (opcion == "current") {
                reproductor.current();
            }
            else if (opcion == "play") {
                string sonando = reproductor.play();
                cout << "Sonando " << sonando << "\n";
            }
            else if (opcion == "totalTime") {
                cout << "Tiempo total " << reproductor.totalTime() << "\n";
            }
            else if (opcion == "recent") {
                int n;
                cin >> n;

                auto const& recientes = reproductor.recent(n);
                if (recientes.empty()) cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << recientes.size() << " mas recientes\n";
                    for (auto const& cancion : recientes) cout << cancion << "\n";
                }
                
            }
            else if (opcion == "deleteSong") {
                cin >> cancion;
                reproductor.deleteSong(cancion);
            }

        } catch (std::domain_error &exception) {
            cout << exception.what() << "\n";
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
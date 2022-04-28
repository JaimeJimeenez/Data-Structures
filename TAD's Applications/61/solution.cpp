#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class Supermercado {
public:
    Supermercado(int num_cajas) : num_cajas(num_cajas), colas(num_cajas) { }

    void nuevo_cliente(const string& cod_cliente, int num_cola) {
        if (num_cola < 0 || num_cola >= num_cajas) throw
            domain_error("Cola inexistente");
        if (clientes.count(cod_cliente)) throw
            domain_error("Cliente duplicado");
        
        colas[num_cola].push_front(cod_cliente);

        clientes[cod_cliente].num_caja = num_cola;
        clientes[cod_cliente].it = colas[num_cola].begin();
    }

    void cambiar_cola(const string& cod_cliente, int num_cola) {
        if (num_cola < 0 || num_cola >= num_cajas) throw
            domain_error("Cola inexistente");
        
        InfoCliente& info = buscar_cliente(cod_cliente);
        if (info.num_caja != num_cola) {
            colas[info.num_caja].erase(info.it);
        
            colas[num_cola].push_front(cod_cliente);
            info.it = colas[num_cola].begin();
            info.num_caja = num_cola;
        } 
        
    }

    int consultar_cliente(const string& cod_cliente) const {
        return buscar_cliente(cod_cliente).num_caja;
    }

    int cuantos_en_cola(int num_cola) const {
        if (num_cola < 0 || num_cola >= num_cajas) throw
            domain_error("Cola inexistente");
        
        return colas[num_cola].size();
    }

    list<string> clientes_en_cola(int num_cola) {
        if (num_cola < 0 || num_cola >= num_cajas) throw
            domain_error("Cola inexistente");
        
        return colas[num_cola];
    }

private:
    int num_cajas;
    vector<list<string>> colas;

    struct InfoCliente {
        int num_caja;
        list<string>::iterator it;
    };

    InfoCliente& buscar_cliente(const string& cod_cliente) {
        if (!clientes.count(cod_cliente)) throw
            domain_error("Cliente inexistente");
        
        return clientes[cod_cliente];
    }

    const InfoCliente& buscar_cliente(const string& cod_cliente) const {
        if (!clientes.count(cod_cliente)) throw
            domain_error("Cliente inexistente");
        
        return clientes.at(cod_cliente);
    }

    unordered_map<string, InfoCliente> clientes;

};

bool tratar_caso() {
    int num_cajas;
    cin >> num_cajas;
    if (!cin) return false;

    Supermercado super(num_cajas);
    string opcion, cod_cliente;
    int num_cola;
    cin >> opcion;
    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo_cliente") {
                cin >> cod_cliente >> num_cola;
                super.nuevo_cliente(cod_cliente, num_cola);
            }
            else if (opcion == "cambiar_cola") {
                cin >> cod_cliente >> num_cola;
                super.cambiar_cola(cod_cliente, num_cola);
            }
            else if (opcion == "consultar_cliente") {
                cin >> cod_cliente;
                int cola = super.consultar_cliente(cod_cliente);
                cout << "El cliente " << cod_cliente << " esta en la cola " << cola << "\n";
            }
            else if (opcion == "cuantos_en_cola") {
                cin >> num_cola;
                int cant = super.cuantos_en_cola(num_cola);
                cout << "En la cola " << num_cola << " hay " << cant << " clientes\n";
            }
            else if (opcion == "clientes_en_cola") {
                cin >> num_cola;
                auto listaCola = super.clientes_en_cola(num_cola);
                
                cout << "En la cola " << num_cola << " estan: ";
                for (auto const it : listaCola) cout << it << " ";
                cout << "\n";
            }
        } catch (std::domain_error& exception) {
            cout << "ERROR: " << exception.what() << endl;
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
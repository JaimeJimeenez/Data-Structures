#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

bool tratar_caso() {
    int value;
    cin >> value;
    if (value == -1) return false;

    stack<int> alturas;
    while (value != -1) {
        while (!alturas.empty() && alturas.top() <= value) 
            alturas.pop();
        
        if (alturas.empty())
            cout << "NO HAY\n";
        else
            cout << alturas.top() << "\n";
            
        alturas.push(value);
        cin >> value;
    }

    cout << "---\n";
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
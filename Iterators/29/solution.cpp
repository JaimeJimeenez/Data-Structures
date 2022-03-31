#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool tratar_caso() {
    string line;
    getline(cin, line);
    if (!cin) return false;

    auto cursor = line.begin();
    auto it = line.begin();

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == "-") {
            cursor = line.begin();
            it = line.erase(it);
        }
        else if (line[i] == "+") {
            cursor = --line.end();
            it = line.erase(it);
        }
        else if (line[i] == "*") {
            ++cursor;
            it = line.erase(it);
        }
        else if (line[i] == "3") {
            cursor = line.erase(cursor);
            it = line.erase(it);
        }
        ++it;
    }
    cout << line <<  endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample1.in");
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
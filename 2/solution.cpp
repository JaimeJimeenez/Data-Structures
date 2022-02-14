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

using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(int elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(int elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }


    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Declaración del método. Impleméntalo antes de la
    // función tratar_caso()
    void escamochar(ListLinkedSingle& dest);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(int elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------


// ¡No olvides indicar el coste del método!
//Coste O(N) siendo n el número de nodos de la lista this
void ListLinkedSingle::escamochar(ListLinkedSingle& dest) {

    Node* prev = nullptr;
    Node* curr = head;
    Node* other = nullptr;

    // Extremo izquierdo
    while (head != nullptr && head->value < 0) {
        prev = curr;
        curr = curr->next;
        head = curr;
        if (dest.empty()) {
            dest.head = prev;
            dest.head->next = nullptr;
            other = dest.head;
        }
        else {
            other->next = prev;
            other = prev;
            other->next = nullptr;
        }
    }

    //Extremo derecho
    Node* aux= nullptr;
    Node* deleteFrom = curr;

    while (curr != nullptr) { //deleteFrom apuntará al último nodo que no hay que eliminar
        if (curr->value >= 0) {
            deleteFrom = curr;
        }
        curr = curr->next;
    }

    if (deleteFrom != nullptr) {
        prev = deleteFrom;
        curr = deleteFrom->next;

        while (curr != nullptr) {
            if (dest.empty()) {
                aux = curr->next;

                dest.head = curr;
                other = dest.head;
                other->next = nullptr;
            }
            else {
                aux = curr->next;

                other->next = curr;
                other = curr;
                other->next = nullptr;
            }

            prev->next = aux;
            curr = aux;
        }
    }
}


void tratar_caso() {

    int N;
    cin >> N;

    ListLinkedSingle list;
    int elem;
    while (N--) {
        cin >> elem;
        list.push_front(elem);
    }

    ListLinkedSingle dest;
    list.escamochar(dest);
    list.display();
    cout << endl;
    dest.display();
    cout << endl;
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

    int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    system("PAUSE");
#endif
    return 0;
}
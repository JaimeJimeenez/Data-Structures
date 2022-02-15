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
  Componente 2: Ivan Pisonero Diaz
*/
//@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }

  ~ListLinkedDouble() { delete_nodes(); }

  void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const int &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }

  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }

  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }

  int size() const { return num_elems; }

  bool empty() const { return num_elems == 0; };

  const int &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  int &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const int &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  int &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const int &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  int &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const { display(std::cout); }
  
  
  // Nuevo método
  // Se implementa más abajo
  void add_to(int index, int val);
  

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
  
  // Nuevos métodos
  // Se implementan más abajo
  static void attach(Node *node, Node *before);  
  static void detach(Node *node);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedDouble::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;

  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

// No olvides el coste!
// Coste constante
void ListLinkedDouble::attach(Node *node, Node *before) {
  node->next = before;
  node->prev = before->prev;
  before->prev->next = node;
  before->prev = node;
}

// No olvides el coste!
// Coste constante
void ListLinkedDouble::detach(Node *node) {
  node->next->prev = node->prev;
  node->prev->next = node->next;
}

// No olvides el coste!
// Coste O(N) con respecto al número de elementos que tiene la lista
void ListLinkedDouble::add_to(int index, int val) {
  Node* curr = head->next;
  
  if (val == 0)
    return;
  
  while (index--) 
    curr = curr->next;

  curr->value += val;
  
  if (curr->next->value < curr->value || curr->prev->value > curr->value) {
    Node* other = curr->next;
    detach(curr);
    if (val > 0) {
      while ((curr->value > other->value) && other != head) 
        other = other->next;
      attach(curr, other);
    }
    else {
      other = other->prev;
      while ((curr->value < other->prev->value) && other != head->next)
        other = other->prev;
      attach(curr, other);
    }
  }
}


//}}}  

bool tratar_caso() {
  
  int M, i, N;
  cin >> M >> i >> N;
  if (M == 0 && i == 0 && N == 0)
    return false;
  
  ListLinkedDouble list;
  while (M--) {
    int value;
    cin >> value;
    list.push_back(value);
  }
  list.add_to(i, N);
  cout << list << endl;
  return true;
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
  
  while(tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

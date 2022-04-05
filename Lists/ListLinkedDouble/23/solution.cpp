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

#include <cassert>
#include <iostream>
#include <fstream>

#ifndef __LIST_LINKED_DOUBLE_H
#define __LIST_LINKED_DOUBLE_H

template <typename T> class ListLinkedDouble {
private:
  struct Node {
    T value;
    Node *next;
    Node *prev;
  };

  template <typename U> class gen_iterator;

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

  void push_front(const T &elem) { insert(cbegin(), elem); }

  void push_back(const T &elem) { insert(cend(), elem); }

  void pop_front() { erase(cbegin()); }

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

  const T &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  T &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const T &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  T &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const T &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  T &operator[](int index) {
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

  using iterator = gen_iterator<T>;
  using const_iterator = gen_iterator<const T>;

  iterator begin() { return iterator(head, head->next); }

  iterator end() { return iterator(head, head); }

  const_iterator begin() const { return const_iterator(head, head->next); }

  const_iterator end() const { return const_iterator(head, head); }

  const_iterator cbegin() const { return const_iterator(head, head->next); }

  const_iterator cend() const { return const_iterator(head, head); }

  template <typename U>
  gen_iterator<U> insert(gen_iterator<U> it, const T &elem) {
    // Comprobamos que el iterador pertenece a la misma
    // lista en la que realizamos la inserción.
    assert(it.head == head);
    Node *new_node = new Node{elem, it.current, it.current->prev};
    it.current->prev->next = new_node;
    it.current->prev = new_node;
    num_elems++;
    return gen_iterator<U>(head, new_node);
  }

  template <typename U> gen_iterator<U> erase(gen_iterator<U> it) {
    // Comprobamos que el iterador pertenece a la misma
    // lista en la que realizamos la inserción, y que no
    // estamos en el último elemento.
    assert(it.head == head && it.current != head);
    Node *target = it.current;
    it.current->prev->next = it.current->next;
    it.current->next->prev = it.current->prev;
    gen_iterator<U> result(head, it.current->next);
    delete target;
    num_elems--;
    return result;
  }

  template <typename Predicate>
  void remove_if(Predicate pred) {
      Node* curr = head->next;
      while (curr != head) {
          Node* sig = curr->next;
          if (pred.notValid(curr->value.getEdad())) dettach(curr);
          curr = sig; 
      }
  }

  void dettach(Node* node) {
      assert(node != nullptr);
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
      num_elems--;
  }

private:
  Node *head;
  int num_elems;

  template <typename U> class gen_iterator {
  public:
    gen_iterator &operator++() {
      assert(current != head);
      current = current->next;
      return *this;
    }

    gen_iterator operator++(int) {
      assert(current != head);
      gen_iterator antes = *this;
      current = current->next;
      return antes;
    }

    U &operator*() const {
      assert(current != head);
      return current->value;
    }

    bool operator==(const gen_iterator &other) const {
      return (head == other.head) && (current == other.current);
    }

    bool operator!=(const gen_iterator &other) const {
      return !(*this == other);
    }

    friend class ListLinkedDouble;

  private:
    gen_iterator(Node *head, Node *current) : head(head), current(current) {}
    Node *head;
    Node *current;
  };

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
};

template <typename T>
typename ListLinkedDouble<T>::Node *ListLinkedDouble<T>::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

template <typename T> void ListLinkedDouble<T>::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble &other) {
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

template <typename T>
void ListLinkedDouble<T>::display(std::ostream &out) const {
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

template <typename T>
std::ostream &operator<<(std::ostream &out, const ListLinkedDouble<T> &l) {
  l.display(out);
  return out;
}

#endif

using namespace std;

class Persona {
private:
    int edad;
    string nombre;
public:
    Persona() : edad(0), nombre("") { }
    Persona(int edad, string nombre) : edad(edad), nombre(nombre) { }

    int getEdad() const { return edad; }

    void print() {
        cout << nombre << endl;
    }
};

class Predicate {
private:
    int min, max;
public:
    Predicate(int min, int max) : min(min), max(max) { }

    bool notValid(int elem) { return elem < min || elem > max; }
};

bool tratar_caso() {
    int N, min, max;
    cin >> N >> min >> max;
    if (N == 0 && min == 0 && max == 0) return false;

    ListLinkedDouble<Persona> lista;
    string nombre;
    int edad;
    while (N--) {
        cin >> edad;
        getline(cin, nombre);
        lista.push_back({ edad, nombre });
    }

    Predicate pred(min, max);
    lista.remove_if(pred);

    while (!lista.empty()) {
        lista.front().print();
        lista.pop_front();
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

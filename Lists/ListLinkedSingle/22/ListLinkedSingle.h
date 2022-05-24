/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
 /*
  * Implementación del TAD Lista mediante listas enlazadas simples.
  *
  * Esta versión introduce el constructor de copia.
  */

#ifndef __LIST_LINKED_SINGLE_H
#define __LIST_LINKED_SINGLE_H

#include <iostream>
#include <fstream>
#include <cassert>

/* --------------------------------------------------------------------
 * Clase ListLinkedSingle
 * --------------------------------------------------------------------
 * Implementa el TAD lista mediante una lista enlazada simple con
 * nodo fantasma y punteros al primer y último elemento.
 * --------------------------------------------------------------------
 */

template<typename T>
class ListLinkedSingle {
private:
  struct Node {
    T value;
    Node *next;
  };

public:
  ListLinkedSingle(): num_elems(0) { 
    head = new Node;
    head->next = nullptr;
    last = head;
  }
  
  ~ListLinkedSingle() {
    delete_list(head);
  }

  ListLinkedSingle(const ListLinkedSingle &other)
    : head(copy_nodes(other.head)), num_elems(other.num_elems) {
      last = last_node();
  }

  void push_front(const T &elem) {
    Node *new_node = new Node { elem, head->next };
    if (head->next == nullptr) { last = new_node; }
    head->next = new_node;
    num_elems++;
  }

  void push_back(const T &elem);

  void pop_front() {
    assert (num_elems > 0);
    Node *old_head = head->next;
    head->next = head->next->next;
    if (head->next == nullptr) { last = head; }
    delete old_head;
    num_elems--;
  }

  void pop_back();

  int size() const {
    return num_elems;
  }

  bool empty() const {
    return num_elems == 0;
  };
  
  const T & front() const {
    assert (num_elems > 0);
    return head->next->value;
  }

  T & front() {
    assert (num_elems > 0);
    return head->next->value;
  }

  const T & back() const {
    return last->value;
  }

  T & back() {
    return last->value;
  }
  
  const T & operator[](int index) const {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  T & operator[](int index) {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  ListLinkedSingle & operator=(const ListLinkedSingle &other) {
    if (this != &other) {
      delete_list(head);
      head = copy_nodes(other.head);
      last = last_node();
      num_elems = other.num_elems;
    }
    return *this;
  }

  void display(std::ostream &out) const;
  
  void display() const {
    display(std::cout);
  }
  
  void unzip(ListLinkedSingle &dest);

  void attach(Node* node, Node* before);

  void dettach(Node* node, Node* before);

private:
  Node *head;
  Node *last;
  int num_elems;

  void delete_list(Node *start_node);
  Node *last_node() const;
  Node *nth_node(int n) const;
  Node *copy_nodes(Node *start_node) const;

};

template<typename T>
typename ListLinkedSingle<T>::Node * ListLinkedSingle<T>::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
    return result;
  } else {
    return nullptr;
  }
}

template<typename T>
void ListLinkedSingle<T>::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->next);
    delete start_node;
  }
}

template<typename T>
void ListLinkedSingle<T>::push_back(const T &elem) {
  Node *new_node = new Node { elem, nullptr };
  last->next = new_node;
  last = new_node;
  num_elems++;
}

template<typename T>
void ListLinkedSingle<T>::pop_back() {
  assert (num_elems > 0);
  Node *previous = head;
  Node *current = head->next;

  while (current->next != nullptr) {
    previous = current;
    current = current->next;
  }

  delete current;
  previous->next = nullptr;
  last = previous;
  num_elems--;
}

template<typename T>
typename ListLinkedSingle<T>::Node * ListLinkedSingle<T>::last_node() const {
  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  return current;
}

template<typename T>
typename ListLinkedSingle<T>::Node * ListLinkedSingle<T>::nth_node(int n) const {
  assert (0 <= n);
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->next;
  }

  return current;
}

template<typename T>
void ListLinkedSingle<T>::display(std::ostream &out) const {
  out << "[";
  if (head->next != nullptr) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != nullptr) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

template<typename T>
std::ostream & operator<<(std::ostream &out, const ListLinkedSingle<T> &l) {
  l.display(out);
  return out;
}

template<typename T>
void ListLinkedSingle<T>::dettach(Node* node, Node* prev) {
  prev->next = node->next;
  node->next = nullptr;
}

template<typename T>
void ListLinkedSingle<T>::attach(Node* node, Node* last_node) {
  last_node->next = node;
  node->next = nullptr;
}
 
template <typename T> 
void ListLinkedSingle<T>::unzip(ListLinkedSingle &dest) {
  Node* curr = head->next;
  Node* prev = head;
  bool odd = false;

  while (curr != nullptr) {
    if (odd) {
      Node* aux = curr->next;
      dettach(curr, prev);
      attach(curr, dest.last);
      dest.last = curr;
      curr = aux;
      dest.num_elems++;
      this->num_elems--;
    }
    else {
      prev = curr;
      curr = curr->next;
    }
    odd = !odd;
  }
}

#endif
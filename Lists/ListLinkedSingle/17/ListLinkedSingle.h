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

#include <cassert>
#include <iostream>
#include <string>

class ListLinkedSingle {
private:
  struct Node {
    int value;
    Node *next;
  };

public:
  ListLinkedSingle(): head(nullptr) { }
  ~ListLinkedSingle() {
    delete_list(head);
  }

  ListLinkedSingle(const ListLinkedSingle &other)
    : head(copy_nodes(other.head)) { }

  void push_front(const int &elem) {
    Node *new_node = new Node { elem, head };
    head = new_node;
  }

  void push_back(const int &elem);

  void pop_front() {
    assert (head != nullptr);
    Node *old_head = head;
    head = head->next;
    delete old_head;
  }

  void pop_back();

  int size() const;

  bool empty() const {
    return head == nullptr;
  };
  
  const int & front() const {
    assert (head != nullptr);
    return head->value;
  }

  int & front() {
    assert (head != nullptr);
    return head->value;
  }

  const int & back() const {
    return last_node()->value;
  }

  int & back() {
    return last_node()->value;
  }
  
  const int & at(int index) const {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  int & at(int index) {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  void display(std::ostream &out) const;
  void display() const {
    display(std::cout);
  }

  void reverseSegment(int init, int fin);

private:
  Node *head;

  void delete_list(Node *start_node);
  Node *last_node() const;
  Node *nth_node(int n) const;
  Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
    return result;
  } else {
    return nullptr;
  }
}

void ListLinkedSingle::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->next);
    delete start_node;
  }
}

void ListLinkedSingle::push_back(const int &elem) {
  Node *new_node = new Node { elem, nullptr };
  if (head == nullptr) {
    head = new_node;
  } else {
    last_node()->next = new_node;
  }
}

void ListLinkedSingle::pop_back() {
  assert (head != nullptr);
  if (head->next == nullptr) {
    delete head;
    head = nullptr;
  } else {
    Node *previous = head;
    Node *current = head->next;

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

  Node *current = head;
  while (current != nullptr) {
    num_nodes++;
    current = current->next;
  }

  return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
  assert (head != nullptr);
  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
  assert (0 <= n);
  int current_index = 0;
  Node *current = head;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
  out << "[";
  if (head != nullptr) {
    out << head->value;
    Node *current = head->next;
    while (current != nullptr) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

void ListLinkedSingle::reverseSegment(int init, int fin) {
    Node* prev = nullptr;
    Node* node_init = head;
    Node* node_end = head;

    while (init--) {
        prev = node_init;
        node_init = node_init->next;
        node_end = node_end->next;
    }
    std::cout << node_end->value << std::endl;

    fin--;
    Node* sig = node_init->next;
    while (fin--) {
        if (prev != nullptr) {
            prev->next = sig;
            node_init->next = sig->next;
            sig->next = node_init;
            sig = node_init->next;
            std::cout << sig->value << std::endl;
            
            display();
            std::cout << std::endl;
        }
    }
}

#endif
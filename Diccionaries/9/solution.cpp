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
  Componente 2: Ivan Pisonero Díaz
*/
//@ </answer>
 
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <ctype.h>


/* 
  Implementación de la clase BinTree para representar árboles binarios.
 */

template<class T>
class BinTree {
public:

  BinTree(): root_node(nullptr) { }
  
  BinTree(const T &elem): root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }
  
  BinTree(const BinTree &left, const T &elem, const BinTree &right)
    :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }
  

  bool empty() const {
    return root_node == nullptr;
  }

  const T & root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert (root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const {
    display_node(root_node, out);
  }
  
private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right): elem(elem), left(left), right(right) { }

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }

};

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 * 
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert (c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert (c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

/*
 * Clase que implementa diccionarios mediante árboles binarios de búsqueda
 */

template <typename K, typename V, typename ComparatorFunction = std::less<K>>
class MapTree {
private:
  template <typename S> class iterator_gen;

public:
  struct MapEntry {
    const K key;
    V value;

    MapEntry(K key, V value) : key(key), value(value) {}
    MapEntry(K key) : key(key), value() {}
  };

  using const_iterator = iterator_gen<const MapEntry>;
  using iterator = iterator_gen<MapEntry>;

  MapTree() : root_node(nullptr), num_elems(0) {}
  MapTree(ComparatorFunction less_than)
      : root_node(nullptr), num_elems(0), less_than(less_than) {}
  MapTree(const MapTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  ~MapTree() { delete_nodes(root_node); }

  void insert(const MapEntry &entry) {
    auto [new_root, inserted] = insert(root_node, entry);
    this->root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const K &key) const {
    return search(root_node, key) != nullptr;
  }

  const V &at(const K &key) const {
    Node *result = search(root_node, key);
    assert(result != nullptr);
    return result->entry.value;
  }

  V &at(const K &key) {
    Node *result = search(root_node, key);
    assert(result != nullptr);
    return result->entry.value;
  }

  V &operator[](const K &key) {
    auto [inserted, new_root, found_node] = search_or_insert(root_node, key);
    this->root_node = new_root;
    if (inserted)
      num_elems++;
    return found_node->entry.value;
  }

  void erase(const K &key) {
    auto [new_root, erased] = erase(root_node, key);
    this->root_node = new_root;
    if (erased) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  MapTree &operator=(const MapTree &other) {
    if (this != &other) {
      num_elems = other.num_elems;
      delete_nodes(root_node);
      root_node = copy_nodes(other.root_node);
    }
    return *this;
  }

  void display(std::ostream &out) const {
    out << "{";
    display(root_node, out);
    out << "}";
  }

  iterator begin() { return iterator(root_node); }

  iterator end() { return iterator(); }

  const_iterator begin() const { return const_iterator(root_node); }

  const_iterator end() const { return const_iterator(); }

  const_iterator cbegin() { return const_iterator(root_node); }

  const_iterator cend() { return const_iterator(); }

private:
  struct Node {
    Node *left;
    MapEntry entry;
    Node *right;

    Node(Node *left, const MapEntry &entry, Node *right)
        : left(left), entry(entry), right(right) {}
  };

  Node *root_node;
  int num_elems;
  ComparatorFunction less_than;

  template <typename S> class iterator_gen {
  public:
    S &operator*() const {
      assert(!st.empty());
      return st.top()->entry;
    }

    S *operator->() const { return &operator*(); }

    iterator_gen &operator++() {
      assert(!st.empty());
      Node *top = st.top();
      st.pop();
      descend_and_push(top->right, st);
      return *this;
    }

    iterator_gen operator++(int) {
      iterator_gen previous = *this;
      ++(*this);
      return previous;
    }

    bool operator==(const iterator_gen &other) { return st == other.st; }

    bool operator!=(const iterator_gen &other) {
      return !this->operator==(other);
    }

  private:
    friend class MapTree;

    iterator_gen() {}

    iterator_gen(Node *root) { descend_and_push(root, st); }

    std::stack<Node *> st;

    static void descend_and_push(Node *node, std::stack<Node *> &st) {
      Node *current = node;
      while (current != nullptr) {
        st.push(current);
        current = current->left;
      }
    }
  };

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->entry,
                      copy_nodes(node->right));
    }
  }

  static void delete_nodes(const Node *node) {
    if (node != nullptr) {
      delete_nodes(node->left);
      delete_nodes(node->right);
      delete node;
    }
  }

  std::pair<Node *, bool> insert(Node *root, const MapEntry &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (less_than(elem.key, root->entry.key)) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (less_than(root->entry.key, elem.key)) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  std::tuple<bool, Node *, Node *> search_or_insert(Node *root, const K &key) {
    if (root == nullptr) {
      Node *new_node = new Node(nullptr, {key}, nullptr);
      return {true, new_node, new_node};
    } else if (less_than(key, root->entry.key)) {
      auto [inserted, new_root, found_node] = search_or_insert(root->left, key);
      root->left = new_root;
      return {inserted, root, found_node};
    } else if (less_than(root->entry.key, key)) {
      auto [inserted, new_root, found_node] =
          search_or_insert(root->right, key);
      root->right = new_root;
      return {inserted, root, found_node};
    } else {
      return {false, root, root};
    }
  }

  std::pair<Node *, bool> erase(Node *root, const K &key) {
    if (root == nullptr) {
      return {root, false};
    } else if (less_than(key, root->entry.key)) {
      auto [new_root_left, erased] = erase(root->left, key);
      root->left = new_root_left;
      return {root, erased};
    } else if (less_than(root->entry.key, key)) {
      auto [new_root_right, erased] = erase(root->right, key);
      root->right = new_root_right;
      return {root, erased};
    } else {
      return {remove_root(root), true};
    }
  }

  static Node *remove_root(Node *root) {
    Node *left_child = root->left, *right_child = root->right;
    delete root;
    if (left_child == nullptr && right_child == nullptr) {
      return nullptr;
    } else if (left_child == nullptr) {
      return right_child;
    } else if (right_child == nullptr) {
      return left_child;
    } else {
      auto [lowest, new_right_root] = remove_lowest(right_child);
      lowest->left = left_child;
      lowest->right = new_right_root;
      return lowest;
    }
  }

  static std::pair<Node *, Node *> remove_lowest(Node *root) {
    assert(root != nullptr);
    if (root->left == nullptr) {
      return {root, root->right};
    } else {
      auto [removed_node, new_root_left] = remove_lowest(root->left);
      root->left = new_root_left;
      return {removed_node, root};
    }
  }

  Node *search(Node *root, const K &key) const {
    if (root == nullptr) {
      return nullptr;
    } else if (less_than(key, root->entry.key)) {
      return search(root->left, key);
    } else if (less_than(root->entry.key, key)) {
      return search(root->right, key);
    } else {
      return root;
    }
  }

  static void display(Node *root, std::ostream &out) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->entry.key << " -> " << root->entry.value;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &out, const MapTree<K, V> &map) {
  map.display(out);
  return out;
}

/*
 * Analizador léxico del lenguaje
 */


class Lexer {
public:
  Lexer(std::istream &in): in(in) { }

  std::string peek() {
    if (next != "") {
      return next;
    } else {
      next = read_next();
      return next;
    }
  }

  std::string get() {
    std::string result = peek();
    next = "";
    return result;
  }

private:
  std::istream &in;

  std::string read_next() {
    std::ostringstream result;
    char current;
    in >> current;
    while (iswspace(current)) {
      in >> current;
    }


    if (isdigit(current)) {
      result << current;
      while (isdigit(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (isalpha(current)) {
      result << current;
      while (isalnum(in.peek())) {
        in >> current;
        result << current;
      }
    } else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
      result << current;
    } else if (current == ':') {
      result << current;
      in >> current;
      if (current != '=') throw std::domain_error(std::string("invalid token: ") + current);
      result << current;
    } else {
      throw std::domain_error(std::string("invalid_token: ") + current);
    }

    return result.str();
  }



private:
  std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
  Parser(std::istream &in): l(in) { }

  BinTree<std::string> parse() {
    return S();
  }

private:
  Lexer l;

  bool is_identifier(const std::string &token) {
    return (!token.empty() && isalpha(token[0]));
  }

  bool is_identifier_or_number(const std::string &token) {
    return (!token.empty() && isalnum(token[0]));
  }

    
  BinTree<std::string> S() {
    std::string identifier = l.get();
    if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

    std::string equal = l.get();
    if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

    BinTree<std::string> rhs = E();

    std::string semicolon = l.get();
    if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

    return { { identifier }, ":=", rhs };
  }

  BinTree<std::string> E() {
    BinTree<std::string> term = T();
    return Ep(term);
  }

  BinTree<std::string> Ep(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "+" || op == "-") {
      l.get();
      BinTree<std::string> term = T();
      return Ep({ left, op, term });
    } else {
      return left;
    }
  }

  BinTree<std::string> T() {
    BinTree<std::string> factor = F();
    return Tp(factor);
  }

  BinTree<std::string> Tp(const BinTree<std::string> &left) {
    std::string op = l.peek();
    if (op == "*") {
      l.get();
      BinTree<std::string> factor = F();
      return Tp({left, "*", factor});      
    } else {
      return left;
    }
  }

  BinTree<std::string> F() {
    std::string next = l.get();
    if (is_identifier_or_number(next)) {
      return { next };
    } else if (next == "(") {
      BinTree<std::string> inner = E();
      std::string closing = l.get();
      if (closing != ")") throw std::domain_error(") expected, found " + closing);
      return inner;
    } else {
      throw std::domain_error("number or identifier expected, found " + next);
    }
  }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream &in) {
  return Parser(in).parse();
}

using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 * 
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
/*@ <answer> */
 
bool esOperador(const string& c) {
  return (c == "+" || c == "-" || c == "*");
}

bool esVariable(const string &c) {
  return !(isdigit(c[0]));
}

void resultado(const MapTree<string, int> &resultados) {
  for (auto elem : resultados)
    cout << elem.key << " = " << elem.value << endl;
}

void rellenarPila(BinTree<string> arbol, stack<string> &pila) {
  pila.push(arbol.root());

  // Si se trata de nodos internos
  if (esOperador(arbol.root())) { 
    rellenarPila(arbol.left(), pila);
    rellenarPila(arbol.right(), pila);
  }

}

/* Tres casos posibles:
      1. Se trata de un operador
      2. Se trata de una variable
      3. Se trata de un número
*/
int calcular(MapTree<string, int> &resultados, BinTree<string> const& arbol) {
  stack<string> pila;
  rellenarPila(arbol, pila);

  stack<int> numeros;
  while (!pila.empty()) {

    if (esOperador(pila.top())) {
      int resultado = numeros.top(); numeros.pop();
      if (pila.top() == "+")
        resultado += numeros.top();
      else if (pila.top() == "-")
        resultado -= numeros.top();
      else
        resultado *= numeros.top();
      
      numeros.pop();
      pila.pop(); 
      numeros.push(resultado); 
    }
    else {
      if (esVariable(pila.top())) {
        int numero = resultados.at(pila.top()); pila.pop();
        numeros.push(numero);
      }
      else {
        numeros.push(stoi(pila.top(), nullptr, 10));
        pila.pop();
      }
    }
  }

  return numeros.top();
}

// Coste O(N * M) siendo N el número de variables y M la longitud de las expresiones de dichas variables (representadas por nodos del arbol)
bool tratar_caso() {
  int N;
  cin >> N;
  if (N == 0) return false;

  MapTree<string, int> resultados;
  while (N--) {
    BinTree<string> arbol = parse(cin);
    string var = arbol.left().root();
    resultados[var] = calcular(resultados, arbol.right());
  }

  resultado(resultados);
  cout << "---\n";
  return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

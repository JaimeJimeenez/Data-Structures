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

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>
#include <algorithm>

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }
  
  int size() const { return size(this->root_node); }

  int height() const { return height(this->root_node); }

  int children() const { return children(this->root_node); }

private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

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

  int size(const NodePointer &root) const {
    if (root == nullptr)
        return 0;
    return 1 + size(root->left) + size(root->right);
  }

  int height(const NodePointer &root) const {
    if (root == nullptr)
        return 0;
    
    return 1 + std::max(height(root->right), height(root->left));
  }

  int children(const NodePointer &root) const {
    if (root == nullptr)
        return 0;
    else if (root->right == nullptr && root->left == nullptr)
        return 1;
    else
        return children(root->right) + children(root->left); 
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

using namespace std;

template<typename T>
tuple<bool T, T> binaray_search_aux(const BinTree<T> & arbol) {
    if (arbol.empty())
        return { true, T(), T() };
    
    auto [abb_izq, min_izq, max_izq] = binaray_search_aux(arbol.left());
    auto [abb_der, min_der, max_der] = binaray_search_aux(arbol.rigth());

    T menor = arbol.left().empty() ? arbol.root() : menor_izq;
    T mayor = arbol.right().empty() ? arbol.root() : mayor_der;
    bool es_abb = abb_izq && abb_der && arbol.root() > max_izq && arbol.root() < min_izq;

    return [es_abb, menor, mayor];
}

template<typename T>
bool binary_search(const BinTree<T> &arbol) {
    return get<0>(binaray_search_aux(arbol));
}

void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << (binary_search(t) ? "SI" : "NO") << endl;
}

int main() {

    int num_casos;
    cin >> num_casos;

    while (num_casos--)
        tratar_caso();
}
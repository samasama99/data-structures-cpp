#include <iostream>

template <typename T, class Comp = std::greater<T>> class BinarySearchTree {
private:
  template <typename Obj, typename C = std::greater<Obj>> struct BSTnode {
    Obj element;
    BSTnode *left;
    BSTnode *right;

    BSTnode(Obj el, BSTnode *l = nullptr, BSTnode *r = nullptr)
        : element(el), left(l), right(r){};

    static BSTnode *createNode(Obj el, BSTnode *l = nullptr,
                               BSTnode *r = nullptr) {
      return new BSTnode(el, l, r);
    };
  };

public:
  typedef T value_type;
  typedef Comp compare;
  typedef BSTnode<value_type> node;

private:
  bool findHelper(node *head, value_type elem) const {
    if (head == nullptr)
      return false;
    if (head->element == elem)
      return true;
    return findHelper(head->left, elem) || findHelper(head->right, elem);
  }

  void printHelper(node *head, size_t depth = 0) const {
    if (head == nullptr)
      return;
    printHelper(head->left, depth + 1);
    std::cout << std::string(depth * 2, ' ') << head->element << '\n';
    printHelper(head->right, depth + 1);
  }

  node *insertHelper(node *head, T nelem) {
    if (head == nullptr)
      return new BSTnode<T>(nelem);
    if (c(head->element, nelem))
      head->left = insertHelper(head->left, nelem);
    if (c(nelem, head->element))
      head->right = insertHelper(head->right, nelem);
    return head;
  }

public:
  BinarySearchTree() : root(NULL), c(compare()){};

  bool find(value_type el) { return findHelper(root, el); }

  void print() { printHelper(root); }

  void insert(value_type el) { root = insertHelper(root, el); }

private:
  node *root;
  compare c;
};

int main() {
  BinarySearchTree<int, std::greater<int>> tree;
  tree.insert(5);
  tree.insert(1);
  tree.insert(6);
  tree.insert(9);
  tree.insert(2);
  tree.insert(0);
  tree.insert(-1);
  tree.insert(3);
  tree.print();
  std::cout << '\n';
  std::cout << (tree.find(10) ? "found" : "not found") << '\n';
  std::cout << (tree.find(2) ? "found" : "not found") << '\n';
}

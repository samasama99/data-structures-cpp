#include <cmath>
#include <iostream>
#include <utility>

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &pr) {
  os << "{ ";
  os << pr.first;
  os << ", ";
  os << pr.second;
  os << " }";
  return os;
}

template <typename T, typename U> struct keyCompare {
  bool operator()(const std::pair<T, U> &x, const std::pair<T, U> &y) const {
    return x.first > y.first;
  }
};

template <typename T, class Comp = std::greater<T>> class binarySearchTree {
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
  node *remove(node *head, value_type el) {
    if (head == nullptr)
      return nullptr;
    if (c(head->element, el))
      head->left = removeHelper(head->left, el);
    else if (c(el, head->element))
      head->right = removeHelper(head->right, el);
    else {
      if (!head->left && !head->right) {
        return nullptr;
      } else if (head->left == nullptr) {
        node *tmp = head->right;
        delete head;
        return tmp;
      } else if (head->right == nullptr) {
        node *tmp = head->left;
        delete head;
        return tmp;
      }
      node *tmp = deepestHelper(head->right);
      head->element = tmp->element;
      head->right = removeHelper(head->right, tmp->element);
    }
    return head;
  }

  bool find(node *head, value_type elem) const {
    if (head == nullptr)
      return false;
    if (!c(head->element, elem) && !c(elem, head->element))
      return true;
    return findHelper(head->left, elem) || findHelper(head->right, elem);
  }

  void print(node *head, size_t depth = 0) const {
    if (head == nullptr) {
      // std::cout << std::string(pow(depth, 2), '\t') << "null" << "\n\n";
      return;
    }
    print(head->left, depth + 1);
    std::cout << std::string(depth, '\t') << head->element << "\n\n";
    print(head->right, depth + 1);
  }

  node *insert(node *head, T nelem) {
    if (head == nullptr)
      return new node(nelem);
    if (c(head->element, nelem))
      head->left = insert(head->left, nelem);
    if (c(nelem, head->element))
      head->right = insert(head->right, nelem);
    if (!c(head->element, nelem) && !c(nelem, head->element))
      head->element = nelem;
    return head;
  }

  void freeAll(node *head) {
    if (head == nullptr)
      return;
    node *left = head->left;
    node *right = head->right;
    delete head;
    freeAll(left);
    freeAll(right);
  }

  node *deepest(node *head) {
    if (head == nullptr)
      return nullptr;
    if (head->left == nullptr)
      return head;
    return deepestHelper(head->left);
  }

public:
  binarySearchTree() : root(nullptr), c(compare()){};
  ~binarySearchTree() {
    if (root)
      freeAll();
  };

  bool find(value_type el) { return findHelper(root, el); }

  void print() { print(root); }

  void insert(value_type el) { root = insert(root, el); }

  void freeAll() {
    freeAll(root);
    root = nullptr;
  }

  void remove(value_type el) { root = removeHelper(root, el); }

  node *deepest() { return deepest(root); }

private:
  node *root;
  compare c;
};

using std::string;

int main() {
  binarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(9);
  tree.insert(2);
  tree.insert(-10);
  tree.print();
}

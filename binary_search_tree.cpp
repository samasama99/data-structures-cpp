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
  node *removeHelper(node *head, value_type el) {
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

  bool findHelper(node *head, value_type elem) const {
    if (head == nullptr)
      return false;
    if (!c(head->element, elem) && !c(elem, head->element))
      return true;
    return findHelper(head->left, elem) || findHelper(head->right, elem);
  }

  void printHelper(node *head, size_t depth = 0) const {
    if (head == nullptr) {
      std::cout << std::string(pow(depth, 2), '_') << "null" << '\n';
      return;
    }
    printHelper(head->left, depth + 1);
    std::cout << std::string(pow(depth, 2), '_') << head->element << '\n';
    printHelper(head->right, depth + 1);
  }

  node *insertHelper(node *head, T nelem) {
    if (head == nullptr)
      return new node(nelem);
    if (c(head->element, nelem))
      head->left = insertHelper(head->left, nelem);
    if (c(nelem, head->element))
      head->right = insertHelper(head->right, nelem);
    if (!c(head->element, nelem) && !c(nelem, head->element))
      head->element = nelem;
    return head;
  }

  void freeHelper(node *head) {
    if (head == nullptr)
      return;
    node *left = head->left;
    node *right = head->right;
    delete head;
    freeHelper(left);
    freeHelper(right);
  }

  node *deepestHelper(node *head) {
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

  void print() { printHelper(root); }

  void insert(value_type el) { root = insertHelper(root, el); }

  void freeAll() {
    freeHelper(root);
    root = nullptr;
  }

  void remove(value_type el) { root = removeHelper(root, el); }

  node *deepest() { return deepestHelper(root); }

private:
  node *root;
  compare c;
};

using std::string;

int main() {
}

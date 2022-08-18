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

template <typename T, class Comp = std::less<T>> class binarySearchTree {
private:
  template <typename Obj, typename C = std::less<Obj>> struct BSTnode {
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
      head->left = remove(head->left, el);
    else if (c(el, head->element))
      head->right = remove(head->right, el);
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
      node *tmp = inOrderPredecessor(head);
      head->element = tmp->element;
      head->right = remove(head->right, tmp->element);
    }
    return head;
  }

  bool find(node *head, value_type elem) const {
    if (head == nullptr)
      return false;
    if (!c(head->element, elem) && !c(elem, head->element))
      return true;
    return find(head->left, elem) || find(head->right, elem);
  }

  void print(node *head, size_t depth = 0) const {
    if (head == nullptr) {
      // std::cout << std::string(pow(depth, 2), '\t') << "null" << "\n\n";
      return;
    }
    print(head->right, depth + 1);
    std::cout << std::string(depth, '\t') << head->element << "\n\n";
    print(head->left, depth + 1);
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

  node *theLeftest(node *head) {
    if (head == nullptr)
      return nullptr;
    if (head->left == nullptr)
      return head;
    return theLeftest(head->left);
  }

  node *theRightest(node *head) {
    if (head == nullptr)
      return nullptr;
    if (head->right == nullptr)
      return head;
    return theRightest(head->right);
  }

  node *inOrderSuccessor(node *head) {
    if (head == nullptr)
      return nullptr;
    return theRightest(head->left);
  }

  node *inOrderPredecessor(node *head) {
    if (head == nullptr)
      return nullptr;
    return theLeftest(head->right);
  }

public:
  binarySearchTree() : root(nullptr), c(compare()){};
  ~binarySearchTree() {
    if (root)
      freeAll();
  };

  bool find(value_type el) { return find(root, el); }

  void print() { print(root); }

  void insert(value_type el) { root = insert(root, el); }

  template <typename Type, typename... Types>
  void insert(Type var1, Types... var2) {
    static_assert(std::is_same<value_type, Type>::value,
                  "insert accept only one type");
    insert(var1);

    insert(var2...);
  }

  void freeAll() {
    freeAll(root);
    root = nullptr;
  }

  void remove(value_type el) { root = remove(root, el); }

  node *inOrderSuccessor() { return inOrderSuccessor(root); }
  node *inOrderPredecessor() { return inOrderPredecessor(root); }

private:
  node *root;
  compare c;
};

using std::cerr;
using std::string;

int main() {
  binarySearchTree<int> tree;
  tree.insert(8, 4, 12, 2, 10, 14, 1, 3, 5, 9, 11, 13, 15, 7);
  cerr << tree.inOrderSuccessor()->element << '\n';
  cerr << tree.inOrderPredecessor()->element << '\n';
  // cerr << std::endl;
  // cerr << tree.find(3) << '\n';
  // cerr << tree.find(-100) << '\n';
  // cerr << std::endl;
  tree.print();
  tree.remove(3);
  tree.remove(-100);
  tree.remove(14);
  cerr << std::endl;
  tree.print();
}

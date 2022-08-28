#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr) {
    os << "{ ";
    os << pr.first;
    os << ", ";
    os << pr.second;
    os << " }";
    return os;
}

template <typename T, typename U>
struct keyCompare {
    bool operator()(const std::pair<T, U>& x, const std::pair<T, U>& y) const {
        return x.first > y.first;
    }
};

template <typename T, class Comp = std::greater<T>>
class binarySearchTree {
   private:
    template <typename Obj, typename C = std::less<Obj>>
    struct BSTnode {
        typedef std::shared_ptr<BSTnode<Obj>> node;
        Obj element;
        std::shared_ptr<BSTnode> left;
        std::shared_ptr<BSTnode> right;

        BSTnode(Obj el, node l = nullptr, node r = nullptr)
            : element(el), left(l), right(r){};

        static node createNode(Obj el, node l = nullptr, node r = nullptr) {
            return std::make_shared<BSTnode>(el, l, r);
        };
    };

   public:
    typedef T value_type;
    typedef Comp compare;
    typedef std::shared_ptr<BSTnode<value_type>> node;

   private:
    node* remove(node* head, value_type el) {
        if (head == nullptr)
            return nullptr;
        if (_c(head->element, el))
            head->left = remove(head->left, el);
        else if (_c(el, head->element))
            head->right = remove(head->right, el);
        else {
            if (!head->left && !head->right) {
                return nullptr;
            } else if (head->left == nullptr) {
                node* tmp = head->right;
                return tmp;
            } else if (head->right == nullptr) {
                node* tmp = head->left;
                return tmp;
            }
            node* tmp = inOrderPredecessor(head);
            head->element = tmp->element;
            head->right = remove(head->right, tmp->element);
        }
        return head;
    }

    bool find(node* head, value_type elem) const {
        if (head == nullptr)
            return false;
        if (!_c(head->element, elem) && !_c(elem, head->element))
            return true;
        return find(head->left, elem) || find(head->right, elem);
    }

    node* get(node* head, value_type elem) const {
        if (head == nullptr)
            return nullptr;
        if (!_c(head->element, elem) && !_c(elem, head->element))
            return head;
        auto left = get(head->left, elem);
        auto right = get(head->right, elem);
        return (right) ? right : left;
    }

    void print(node head, size_t depth = 0) const {
        if (head == nullptr) {
            // std::cout << std::string(pow(depth, 2), '\t') << "null" <<
            // "\n\n";
            return;
        }
        print(head->right, depth + 1);
        std::cout << std::string(depth, '\t') << head->element << "\n\n";
        print(head->left, depth + 1);
    }

    node insert(node head, T nelem) {
        if (head == nullptr)
            return BSTnode<value_type>::createNode(nelem);
        if (_c(head->element, nelem))
            head->left = insert(head->left, nelem);
        if (_c(nelem, head->element))
            head->right = insert(head->right, nelem);
        if (!_c(head->element, nelem) && !_c(nelem, head->element))
            head->element = nelem;
        return head;
    }

    node theLeftest(node head) {
        if (head == nullptr)
            return nullptr;
        if (head->left == nullptr)
            return head;
        return theLeftest(head->left);
    }

    node theRightest(node head) {
        if (head == nullptr)
            return nullptr;
        if (head->right == nullptr)
            return head;
        return theRightest(head->right);
    }

    node inOrderSuccessor(node head) {
        if (head == nullptr)
            return nullptr;
        return theRightest(head->left);
    }

    node inOrderPredecessor(node head) {
        if (head == nullptr)
            return nullptr;
        return theLeftest(head->right);
    }

   public:
    binarySearchTree() : _root(nullptr), _c(compare()), _size(0){};

    template <typename Type, typename... Types>
    binarySearchTree(Type var1, Types... var2)
        : _root(nullptr), _c(compare()), _size(0) {
        static_assert(std::is_same<value_type, Type>::value,
                      "insert accept only one type");
        insert(var1);

        insert(var2...);
    }

    ~binarySearchTree(){};

    bool find(value_type el) { return find(_root, el); }

    node get(value_type el) { return get(_root, el); }

    void print() { print(_root); }

    void insert(value_type el) {
        ++_size;
        _root = insert(_root, el);
    }

    template <typename Type, typename... Types>
    void insert(Type var1, Types... var2) {
        static_assert(std::is_same<value_type, Type>::value,
                      "insert accept only one type");
        insert(var1);

        insert(var2...);
    }

    void remove(value_type el) { _root = remove(_root, el); }

    node inOrderSuccessor() { return inOrderSuccessor(_root); }
    node inOrderPredecessor() { return inOrderPredecessor(_root); }

    ////////////////////
    // ROTATIONS

   private:
    node left_rotate(node* head) {
        std::cerr << head << " " << head->element << '\n';
        node temp = head->right;
        std::cerr << temp << "\n";
        head->right = temp->left;
        temp->left = head;
        return temp;
    }

    node left_rotate(node* head, value_type val) {
        if (head == NULL)
            return nullptr;
        if (head->element == val)
            return left_rotate(head);
        if (head->right && head->element < val)
            head->right = left_rotate(head->right, val);
        if (head->left && head->element > val)
            head->left = left_rotate(head->left, val);
        return head;
    }

    node right_rotate(node head) {
        node temp = head->left;
        head->left = temp->right;
        temp->right = head;
        return temp;
    }

    node right_rotate(node head, value_type val) {
        if (head == NULL)
            return nullptr;
        if (head->element == val)
            return right_rotate(head);
        if (head->left && head->element < val)
            head->left = right_rotate(head->left, val);
        if (head->right && head->element > val)
            head->right = right_rotate(head->right, val);
        return head;
    }

    node right_left_rotate(node head, value_type val) {
        if (head == NULL)
            return nullptr;
        if (head->element == val)
            return right_left_rotate(head);
        if (head->left && head->element < val)
            head->left = right_left_rotate(head->left, val);
        if (head->right && head->element > val)
            head->right = right_left_rotate(head->right, val);
        return head;
    }

    node right_left_rotate(node head) {
        head->right = right_rotate(head->right);  // parent
        return left_rotate(head);                 // grandparent
    }

    node left_right_rotate(node head) {
        head->left = left_rotate(head->left);  // parent
        return right_rotate(head);             // grandparent
    }

    node left_right_rotate(node head, value_type val) {
        if (head == NULL)
            return nullptr;
        if (head->element == val)
            return left_right_rotate(head);
        if (head->left && head->element < val)
            head->left = left_right_rotate(head->left, val);
        if (head->right && head->element > val)
            head->right = left_right_rotate(head->right, val);
        return head;
    }

   public:
    void left_rotate(value_type val) { _root = left_rotate(_root, val); }
    void right_rotate(value_type val) { _root = right_rotate(_root, val); }
    void right_left_rotate(value_type val) {
        _root = right_left_rotate(_root, val);
    }
    void left_right_rotate(value_type val) {
        _root = left_right_rotate(_root, val);
    }

   private:
    node _root = nullptr;
    compare _c = compare();
    size_t _size = 0;
};

// using std::cerr;
using std::string;
#define leaks() system("leaks a.out");

int main() {
    binarySearchTree<int> tree(20, 30, 15, 10, 7, 11, 16);
    tree.right_rotate(20);
    tree.print();
}

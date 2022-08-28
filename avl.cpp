// AVL a self balancing binary search tree
// optional : trying to use smart pointers instead of raw pointers

#include <iostream>
#include <memory>

template <class T>
class AVL {
    struct Node {
        T data = T();
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        std::shared_ptr<Node> parent = nullptr;

       public:
        Node(T data) : data(data) {}
    };

   public:
    using node = std::shared_ptr<Node>;
    using size_type = size_t;

   private:
    node left_rotate(node &head) {
        node temp = head->right;
        head->right = temp->left;
        temp->left = head;
        return temp;
    }

    node right_rotate(node &head) {
        node temp = head->left;
        head->left = temp->right;
        temp->right = head;
        return temp;
    }

    node right_left_rotate(node &head) {
        head->right = right_rotate(head->right);  // parent
        return left_rotate(head);                 // grandparent
    }

    node left_right_rotate(node &head) {
        head->left = left_rotate(head->left);  // parent
        return right_rotate(head);             // grandparent
    }
    size_type getMaxLen(const node &head) const {
        if (head == nullptr)
            return 0;
        return 1 + std::max(getMaxLen(head->left), getMaxLen(head->right));
    }

   public:
    size_type getMaxLen() const { return getMaxLen(_root); }
    size_t size() const { return _size; }

    // bool checkIfBalance(node head) {
    //     if (head)
    //         return true;
    //     return abs(getMaxLen(head->left) - getMaxLen(head->right)) <= 1;
    // }

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

    node balance(node &head) {
        int left = getMaxLen(head->left), right = getMaxLen(head->right);
        int diff = abs(left - right);
        if (diff <= 1)
            return head;
        if (left > right) {
            node &llc = head->left->left;
            if (llc)
                return right_rotate(head);
            return left_right_rotate(head);
        }
        node &rrc = head->right->right;
        if (rrc)
            return left_rotate(head);
        return right_left_rotate(head);
    }

    void insert(node& head, node el) {
        if (head == nullptr) {
            head = el;
            _size += 1;
            return;
        }

        if (el->data > head->data)
            insert(head->right, el);
        else if (el->data < head->data)
            insert(head->left, el);

        if (head->right)
            head->right->parent = head;
        if (head->left)
            head->left->parent = head;
        head = balance(head);
    }

    void print(const node &head, size_t depth = 0) const {
        if (head == nullptr)
            return;
        print(head->right, depth + 1);
        std::cout << std::string(depth, '\t') << head->data << "\n\n";
        print(head->left, depth + 1);
    }

    void print() const { print(_root); }

    void insert(T data) {
        if (_root == nullptr) {
            _root = std::make_shared<Node>(data);
            _size += 1;
            return;
        }
        insert(_root, std::make_shared<Node>(data));
    }

    node remove(node &head, T el) {
        if (head == nullptr)
            return nullptr;
        if (head->data > el)
            head->left = remove(head->left, el);
        else if (el > head->data)
            head->right = remove(head->right, el);
        else {
            if (!head->left && !head->right) {
                return nullptr;
            } else if (head->left == nullptr) {
                node tmp = head->right;
                return tmp;
            } else if (head->right == nullptr) {
                node tmp = head->left;
                return tmp;
            }
            node tmp = inOrderPredecessor(head);
            std::cerr << "in order " << tmp->data << '\n';
            head->data = tmp->data;
            head->right = remove(head->right, tmp->data);
        }
        return balance(head);
    }

    void remove(T el) { _root = remove(_root, el); }

   private:
    node _root = nullptr;
    size_type _size = 0;
};

auto main() -> int {
    AVL<int> tree;
    // tree.insert(10);
    // tree.insert(6);
    // tree.insert(7);
    // tree.insert(2);
    // tree.insert(13);
    // tree.insert(11);
    // tree.insert(12);
    // tree.insert(14);

    tree.insert(43);
    tree.insert(18);
    tree.insert(22);
    tree.insert(9);
    tree.insert(21);
    tree.insert(6);
    tree.insert(8);
    tree.insert(20);
    tree.insert(63);
    tree.insert(50);
    tree.insert(62);
    tree.insert(51);
    tree.print();
    tree.remove(21);
    tree.remove(6);
    tree.remove(8);
	std::cerr << "**********\n";
    tree.print();
    // std::cout << tree.getMaxLen() << '\n';
    // std::cout << tree.size() << '\n';
}

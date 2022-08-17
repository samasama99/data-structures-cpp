
template <typename T> struct redBlackTreeNode {
  enum Color { BLACK, RED };
  typedef redBlackTreeNode *node;
  T element;
  node left;
  node right;
  node parent;
  Color c;

  redBlackTreeNode()
      : element(T()), left(nullptr), right(nullptr), parent(nullptr),
        c(BLACK){};

  redBlackTreeNode(T el)
      : element(el), left(nullptr), right(nullptr), parent(nullptr), c(RED){};

  redBlackTreeNode(T el, Color c)
      : element(el), left(nullptr), right(nullptr), parent(nullptr), c(c){};

  redBlackTreeNode(T el, node l = nullptr, node r = nullptr, node p = nullptr,
                   Color c = RED)
      : element(el), left(l), right(r), parent(p), c(c){};
};

template <typename T> class redBlackTree {
public:
  typedef T type;
  typedef redBlackTreeNode<type> node;

  redBlackTree() : root(nullptr) {}

  // node rotateLeft(node head) {
  // }

private:
  node *root;
};

int main() {}

enum Color { BLACK, RED };
enum Position { LEFT, RIGHT };

template <typename K, typename V> struct redBlackTreeNode {

  using key = K;
  using value = V;
  using node = redBlackTreeNode *;

  key k;
  value v;
  node left, right, parent;
  Position position;
  Color color;

  redBlackTreeNode()
      : k(K()), v(V()), left(nullptr), right(nullptr), parent(nullptr),
        color(BLACK){};

  redBlackTreeNode(key k, value v)
      : k(k), v(v), left(nullptr), right(nullptr), position(LEFT),
        parent(nullptr), color(RED){};

  redBlackTreeNode(key k, value v, Color c)
      : k(k), v(v), left(nullptr), right(nullptr), parent(nullptr), color(c){};

  redBlackTreeNode(key k, value v, node l = nullptr, node r = nullptr,
                   node p = nullptr, Color c = RED)
      : k(k), v(v), left(l), right(r), parent(p), color(c){};
};

template <typename K, typename V> class redBlackTree {
public:
  using value_size = unsigned long long;
  using key = K;
  using value = V;
  using Node = redBlackTreeNode<key, value> *;
  redBlackTree() : _root(nullptr) {}

  void updateRelation(Node parent, Node child, Position child_pos) {
    parent->right = child;
    child->parent = parent;
    child->position = child_pos;
  }

private:
  void insert(Node parent, Node new_node) {
    if (new_node->key > parent->key) {
      if (parent->right == nullptr) {
        return updateRelation(parent, new_node, RIGHT);
      }
      return add(parent->right, new_node);
    }
    if (parent->left == nullptr) {
      return updateRelation(parent, new_node, LEFT);
    }
    return add(parent->left, new_node);
  }

  // getColorOfUncle

  void correctTree(Node node) {
    Node parent = node->parent;
    Node grand_parent = node->parent->parent;
    if (parent->position == LEFT) {
      if (grand_parent->right == nullptr || parent->parent->color == BLACK) {
      }
    }
    // if (getColorOfUncle == BLACK)
    //   colorFlip();
  }

  void checkColor(Node node) {
    if (node == nullptr)
      return;
    if (node->color == RED && node->parent->color == RED) {
      correctTree(node);
      checkColor(node->parent);
    }
  }

public:
  void insert(key k, value v) {
    auto node = new Node(k, v);
    _size += 1;
    if (_root == nullptr) {
      _root = node;
      node->color = BLACK;
      return;
    }
    insert(_root, node);
  }

private:
  Node _root;
  value_size _size;
};

int main() {}

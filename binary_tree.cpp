#include <iostream>
#include <stack>
#include <vector>
#include <assert.h>

// inorder traversal (left, node, right)
enum class operation {sum, mult, sub, err};

bool isOperand(char c) { return std::iswalnum(c); }

template <typename Obj> struct BinaryNode {
  Obj element;
  BinaryNode *left;
  BinaryNode *right;
  BinaryNode(Obj el, BinaryNode *left = nullptr, BinaryNode *right = nullptr)
      : element(el), left(left), right(right){};
};

operation charToOp(char c) {
  switch (c) {
    case '+':
      return operation::sum;
    case '*':
      return operation::mult;
    case '-':
      return operation::mult;
  }
  assert(true && "A none reachable case");
  return operation::err;
}

long doOp(long e1, long e2, operation op) {
  switch (op) {
    case operation::sum:
      return e1 + e2;
    case operation::mult:
      return e1 * e2;
    case operation::sub:
      return e1 - e2;
    case operation::err: break;
  }
  assert(true && "A none reachable case");
  return 0;
}

BinaryNode<char> *makeBinaryTreeExpr(std::vector<char> target) {
  std::stack<BinaryNode<char> *> nodes;

  for (auto t : target) {
    if (isOperand(t)) {
      nodes.push(new BinaryNode<char>(t));
    } else {
      auto right = nodes.top();
      nodes.pop();
      auto left = nodes.top();
      nodes.pop();
      nodes.push(new BinaryNode<char>(t, left, right));
    }
  }
  return nodes.top();
};

void printBinaryTreeExpr(BinaryNode<char> *tree) {
  if (!tree)
    return;
  printBinaryTreeExpr(tree->left);
  std::cout << tree->element << ' ';
  printBinaryTreeExpr(tree->right);
}

long evalBinaryTreeExpr(BinaryNode<char> *tree) {
   if (isOperand(tree->element))
    return tree->element - '0';
  return doOp(evalBinaryTreeExpr(tree->left), evalBinaryTreeExpr(tree->right), charToOp(tree->element));
};
;

int main() {
  auto expr = {'1', '2', '+', '3', '4', '5', '+', '*', '*'};
  // 1 + 2 = 3
  // 4 + 5 = 9
  // 3 * 
  auto tree = makeBinaryTreeExpr(expr);
  printBinaryTreeExpr(tree);
  std::cout << "\nres " << evalBinaryTreeExpr(tree) << '\n'; 
}

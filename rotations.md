# rotations :

Left rotation :
  - set temp = grandparent right child
  - set grandparent right child = temp left child
  - set temp left child = grandparent
  - use temp instead of grandparent

``` c++
  Node left_rotate(Node node) {
    Node temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
  }
```

Right rotation :
  - set temp = grandparent left child
  - set grandparent left child = temp right child
  - set temp right child = grandparent
  - use temp instead of grandparent

``` c++

  Node right_rotate(Node node) {
    Node temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
  }

```

Right Left rotation :

``` c++
  Node right_left_rotate(Node node) {
    node->right = right_rotate(node->right); // parent
    return left_rotate(node);                // grandparent
  }

```

Left Rotate rotation :

``` c++
  Node left_right(Node node) {
    node->left = left_rotate(node->left); // parent
    return right_rotate(node);                // grandparent
  }

```

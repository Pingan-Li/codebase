/**
 * @file rb_tree.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
using namespace std;
/**
 * @brief Colors of tree nodes.
 *
 */
enum Color { RED, BLACK };
template <typename T> struct Node {
  T data;       // data
  Color color;  // cloor
  Node *left;   // left child
  Node *right;  // right child
  Node *parent; // parent

  Node(T const &val)
      : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T> class RedBlackTree {
public:
  using NodeType = Node<T>;
  RedBlackTree() : root_(nullptr) {}

  RedBlackTree(RedBlackTree const &) = delete;
  RedBlackTree &operator=(RedBlackTree const &) = delete;
  RedBlackTree(RedBlackTree &&) = delete;
  RedBlackTree &operator=(RedBlackTree &&) = delete;

  virtual ~RedBlackTree() = default;
  /**
   * @brief Insert
   *
   * @param val
   */
  void Insert(T const &val) {
    NodeType *new_node = new NodeType(val);
    NodeType *parent = nullptr;
    NodeType *current = root_;

    // find a position to insert.
    while (current) {
      parent = current;
      if (val < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    new_node->parent = parent;
    // if root is empty then new node is the root.
    if (!parent) {
      root_ = new_node;
    } else if (val < parent->data) {
      // insert at left
      parent->left = new_node;
    } else {
      // insert at right.
      parent->right = new_node;
    }

    FixInsertion(new_node);
  }

private:
  NodeType *root_;

  void RotateLeft(NodeType *node) {
    NodeType *right_child = node->right;
    node->right = right_child->left;
    if (right_child->left) {
      right_child->left->parent = node;
    }
    right_child->parent = node->parent;
    if (!node->parent) {
      root_ = right_child;
    } else if (node == node->parent->left) {
      node->parent->left = right_child;
    } else {
      node->parent->right = right_child;
    }
    right_child->left = node;
    node->parent = right_child;
  }

  void RotateRight(NodeType *node) {
    NodeType *left_child = node->left;
    node->left = left_child->right;
    if (left_child->right) {
      left_child->right->parent = node;
    }
    left_child->parent = node->parent;
    if (!node->parent) {
      root_ = left_child;
    } else if (node == node->parent->left) {
      node->parent->left = left_child;
    } else {
      node->parent->right = left_child;
    }
    left_child->right = node;
    node->parent = left_child;
  }
  /**
   * @brief Fix the balance of the tree after insertion.
   *
   * @param node
   */
  void FixInsertion(NodeType *node) {
    while (node != root_ && node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        NodeType *uncle = node->parent->parent->right;
        if (uncle && uncle->color == RED) { // Case 1:  uncle node is red
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else { // Case 2: uncle node is black or null
          if (node == node->parent->right) {
            node = node->parent;
            RotateLeft(node); // RotateLeft
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RotateRight(node->parent->parent); // RotateRight
        }
      } else {
        NodeType *uncle = node->parent->parent->left;
        if (uncle && uncle->color == RED) { // Case 1: uncle node is red
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else { // Case 2: uncle node is black or null
          if (node == node->parent->left) {
            node = node->parent;
            RotateRight(node); // RotateRight
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RotateLeft(node->parent->parent); // RotateLeft
        }
      }
    }
    root_->color = BLACK; // the root node is always black.
  }
};

int main() {
  RedBlackTree<int> rb_tree;
  rb_tree.Insert(1);
  rb_tree.Insert(2);
  rb_tree.Insert(3);
  rb_tree.Insert(4);
  rb_tree.Insert(5);
  return 0;
}

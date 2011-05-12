#include "binary-tree.h"

#include <stack>
#include <queue>

namespace binarytree {

Node::Node(const int value, Node *parent)
    : value_(value), left_(0), right_(0), parent_(parent) {
}

Node::~Node() {
  if (left_)
    delete left_;
  if (right_)
    delete right_;
}

BinaryTree::BinaryTree() : root_(0) {
}

BinaryTree::~BinaryTree() {
  delete root_;
}

void BinaryTree::Add(const int value) {
  Node *new_node = new Node(value);
  Node *y = 0;
  Node *x = root_;
  while (x) {
    y = x;
    if (value < x->value())
      x = x->left();
    else
      x = x->right();
  }
  new_node->set_parent(y);
  if (!y)
    root_ = new_node;
  else if (value < y->value())
    y->set_left(new_node);
  else
    y->set_right(new_node);
}

Node *BinaryTree::Find(int value) const {
  Node *node = root_;
  while (node && node->value() != value) {
    if (value < node->value())
      node = node->left();
    else
      node = node->right();
  }
  return node;
}

const int BinaryTree::Min() const {
  return Min(root_)->value();  
}

Node *BinaryTree::Min(Node *node) const {
  while (node->left())
    node = node->left();
  return node;
}

Node *BinaryTree::Max(Node *node) const {
  while (node->right())
    node = node->right();
  return node;
}

const int BinaryTree::Max() const {
  return Max(root_)->value();
}

bool BinaryTree::Delete(const int value) {
  Node *n = Find(value);
  if (!n)
    return false;
  Delete(n);
  return true;
}

void BinaryTree::Traverse(std::function<void(Node *)> callback,
                          const TraverseType type) {
  Traverse(root_, callback, type);
}
                          
void BinaryTree::TraverseBreath(std::function<void(Node *)> callback) {
  std::queue<Node *> q;
  q.push(root_);
  while (!q.empty()) {
    Node *current = q.front();
    q.pop();
    if (current->left())
      q.push(current->left());
    if (current->right())
      q.push(current->right());
    callback(current);
  }
}
                          
void BinaryTree::TraverseDepth(std::function<void(Node *)> callback) {
  std::stack<Node *> q;
  q.push(root_);
  while (!q.empty()) {
    Node *current = q.top();
    q.pop();
    if (current->right())
      q.push(current->right());
    if (current->left())
      q.push(current->left());
    callback(current);
  }
}

void BinaryTree::Transplant(Node *u, Node *v) {
  if (!u->parent())
    root_ = v;
  else if (u == u->parent()->left())
    u->parent()->set_left(v);
  else
    u->parent()->set_right(v);
  if (v)
    v->set_parent(u->parent());
}

Node *BinaryTree::Successor(Node *n) {
  if (n->right())
    return Min(n->right());
  Node *y = n->parent();
  while (y && n == y->right()) {
    n = y;
    y = y->parent();
  }
  return y;
}

void BinaryTree::Delete(Node *node) {
  if (!node->left())
    Transplant(node, node->right());
  else if (!node->right())
    Transplant(node, node->left());
  else {
    Node *y = Min(node->right());
    if (y->parent() != node) {
      Transplant(y, y->right());
      y->set_right(node->right());
      y->right()->set_parent(y);
    }
    Transplant(node, y);
    y->set_left(node->left());
    y->left()->set_parent(y);
  }
}

void BinaryTree::Traverse(Node *node, std::function<void(Node *)> callback,
                          const TraverseType type) {
  if (!node)
    return;
  if (type == kPrefix)
    callback(node);
  Traverse(node->left(), callback, type);
  if (type == kInfix)
    callback(node);
  Traverse(node->right(), callback, type);
  if (type == kPostfix)
    callback(node);
}                          


} // namespace binarytree
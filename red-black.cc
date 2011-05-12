#include "red-black.h"

#include <functional>
#include <stack>
#include <queue>

namespace redblack {

Node::Node(const int value, Node *parent) : value_(value), parent_(parent),
                                            left_(0), right_(0), color_(kBlack) {
}

Node::~Node() {
  if (left_) {
    delete left_;
    left_ = 0;
  }
  if (right_) {
    delete right_;
    right_ = 0;
  }
  parent_ = 0;
}

RedBlackTree::RedBlackTree() : nil_(new Node(-1)), root_(nil_) {
  nil_->set_left(nil_);
  nil_->set_right(nil_);
}

RedBlackTree::~RedBlackTree() {
  Node *tmp = nil_;
  Traverse([tmp](Node *node) -> void {
    if (node->left() == tmp)
      node->set_left(0);
    if (node->right() == tmp)
      node->set_right(0);
  }, kPostfix);
  if (root_) {
    delete root_;
    root_ = 0;
  }
  nil_->set_parent(0);
  nil_->set_left(0);
  nil_->set_right(0);
  delete nil_;
}

void RedBlackTree::LeftRotate(Node *x) {
  Node *y = x->right();
  x->set_right(y->left());
  if (y->left() != nil_)
    y->left()->set_parent(x);
  y->set_parent(x->parent());
  if (x->parent() == nil_)
    root_ = y;
  else if (x == x->parent()->left())
    x->parent()->set_left(y);
  else
    x->parent()->set_right(y);
  y->set_left(x);
  x->set_parent(y);
}

void RedBlackTree::RightRotate(Node *x) {
  Node *y = x->left();
  x->set_left(y->right());
  if (y->right() != nil_)
    y->right()->set_parent(x);
  y->set_parent(x->parent());
  if (x->parent() == nil_) 
    root_ = y;
  else if (x == x->parent()->left())
    x->parent()->set_left(y);
  else
    x->parent()->set_right(y);
  y->set_right(x);
  x->set_parent(y);
}

Node *RedBlackTree::Find(int value) const {
  Node *curr = root_;
  while (curr != nil_) {
    if (curr->value() == value)
      return curr;
    if (curr->value() > value)
      curr = curr->left();
    else
      curr = curr->right();
  }
  return 0;
}

const int RedBlackTree::Min() const {
  Node *curr = root_;
  while (curr->left() != nil_)
    curr = curr->left();
  return curr->value();
}

const int RedBlackTree::Max() const {
  Node *curr = root_;
  while (curr->right() != nil_)
    curr = curr->right();
  return curr->value();
}

void RedBlackTree::Add(const int value) {
  Node *to_insert = new Node(value);
  Node *y = nil_;
  Node *x = root_;
  while (x != nil_) {
    y = x; // at the end y contains the parent of x, smart isn't it
    if (to_insert->value() < x->value())
      x = x->left();
    else
      x = x->right();
  }
  to_insert->set_parent(y);
  if (y == nil_)
    root_ = to_insert;
  else if (to_insert->value() < y->value())
    y->set_left(to_insert);
  else
    y->set_right(to_insert);
  to_insert->set_left(nil_);
  to_insert->set_right(nil_);
  to_insert->set_color(kRed);
  FixColoring(to_insert);
}

void RedBlackTree::FixColoring(Node *x) {
  Node *y;
  // doesn't enter in the while loop if node is the root (parent is black)
  // or if x->parent() is root, since root is black. So, element is guaranteed
  // to have an x->parent()->parent() != nil_
  while (x->parent()->color() == kRed) {
    if (x->parent() == x->parent()->parent()->left()) {
      y = x->parent()->parent()->right();
      if (y->color() == kRed) { // the uncle of x is also red
        x->parent()->set_color(kBlack);
        y->set_color(kBlack);
        x->parent()->parent()->set_color(kRed);
        x = x->parent()->parent();
      } else {
        if (x == x->parent()->right()) {
          x = x->parent();
          LeftRotate(x);
        }
        x->parent()->set_color(kBlack);
        x->parent()->parent()->set_color(kRed);
        RightRotate(x->parent()->parent());
      }
    } else {
      y = x->parent()->parent()->left();
      if (y->color() == kRed) { // the uncle of x is also red
        x->parent()->set_color(kBlack);
        y->set_color(kBlack);
        x->parent()->parent()->set_color(kRed);
        x = x->parent()->parent();
      } else {
        if (x == x->parent()->left()) {
          x = x->parent();
          RightRotate(x);
        }
        x->parent()->set_color(kBlack);
        x->parent()->parent()->set_color(kRed);
        LeftRotate(x->parent()->parent());
      }
    }
  }
  root_->set_color(kBlack); // fixes violation of property 2
}

void RedBlackTree::Transplant(Node *u, Node *v) {
  if (u->parent() == nil_)
    root_ = v;
  else if (u == u->parent()->left())
    u->parent()->set_left(v);
  else
    u->parent()->set_right(v);
  v->set_parent(u->parent());
}

Node *RedBlackTree::Successor(Node *n) {
  while (n->left() != nil_)
    n = n->left();
  return n;
}

void RedBlackTree::Delete(Node *node) {
  Node *y = node;
  NodeColor y_original = y->color();
  Node *x;
  if (node->left() == nil_) {
    x = node->right();
    Transplant(node, node->right());
  } else if (node->right() == nil_) {
    x = node->left();
    Transplant(node, node->left());
  } else {
    y = Successor(node->right());
    y_original = y->color();
    x = y->right();
    if (y->parent() == node) {
      x->set_parent(y);
    } else {
      Transplant(y, y->right());
      y->set_right(node->right());
      y->right()->set_parent(y);
    }
    Transplant(node, y);
    y->set_left(node->left());
    y->left()->set_parent(y);
    y->set_color(node->color());
  }
  if (y_original == kBlack)
    FixColoringDelete(x);
}

void RedBlackTree::FixColoringDelete(Node *x) {
  while (x != root_ && x->color() == kBlack) {
    if (x == x->parent()->left()) {
      Node *w = x->parent()->right();
      if (w->color() == kRed) {
        w->set_color(kBlack);
        x->parent()->set_color(kRed);
        LeftRotate(x->parent());
        w = x->parent()->right();
      }
      if (w->left()->color() == kBlack && w->right()->color() == kBlack) {
        w->set_color(kRed);
        x = x->parent();
      } else {
        if (w->right()->color() == kBlack) {
          w->left()->set_color(kBlack);
          w->set_color(kRed);
          RightRotate(w);
          w = x->parent()->right();
        }
        w->set_color(x->parent()->color());
        x->parent()->set_color(kBlack);
        w->right()->set_color(kBlack);
        LeftRotate(x->parent());
        x = root_;
      }
    } else {
      Node *w = x->parent()->left();
      if (w->color() == kRed) {
        w->set_color(kBlack);
        x->parent()->set_color(kRed);
        RightRotate(x->parent());
        w = x->parent()->left();
      }
      if (w->right()->color() == kBlack && w->left()->color() == kBlack) {
        w->set_color(kRed);
        x = x->parent();
      } else {
        if (w->left()->color() == kBlack) {
          w->right()->set_color(kBlack);
          w->set_color(kRed);
          LeftRotate(w);
          w = x->parent()->left();
        }
        w->set_color(x->parent()->color());
        x->parent()->set_color(kBlack);
        w->left()->set_color(kBlack);
        RightRotate(x->parent());
        x = root_;
      }
    }
  }
  x->set_color(kBlack);
}

bool RedBlackTree::Delete(const int value) {
  Node *to_delete = Find(value);
  if (!to_delete)
    return false;
  Delete(to_delete);
  to_delete->set_left(0);
  to_delete->set_right(0);
  delete to_delete;
  return true;
}

void RedBlackTree::Traverse(std::function<void(Node *)> callback, 
                            const TraverseType type) {
  Traverse(root_, callback, type);
}

void RedBlackTree::Traverse(Node *node, std::function<void(Node *)> callback, 
                            const TraverseType type) {
  if (node == nil_)
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

 void RedBlackTree::TraverseBreath(std::function<void(Node *)> callback) {
   std::queue<Node *> q;
   q.push(root_);
   while (!q.empty()) {
     Node *current = q.front();
     q.pop();
     if (current->left() != nil_)
       q.push(current->left());
     if (current->right() != nil_)
       q.push(current->right());
     callback(current);
   }
 }
 
 void RedBlackTree::TraverseDepth(std::function<void(Node *)> callback) {
   std::stack<Node *> q;
   q.push(root_);
   while (!q.empty()) {
     Node *current = q.top();
     q.pop();
     if (current->right() != nil_)
       q.push(current->right());
     if (current->left() != nil_)
       q.push(current->left());
     callback(current);
   }
 }

} // namespace redblack
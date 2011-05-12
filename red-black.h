#ifndef REDBLACK_H_
#define REDBLACK_H_

#include <functional>

namespace redblack {

enum NodeColor {
  kBlack,
  kRed
};

// Properties of red-black trees:
//  1. Every node is labeled with either red or black
//  2. The root node is black
//  3. Every leaf (nil) is black
//  4. If a node is red, both its children are black
//  5. Every simple path between root and any of its desendants goes through 
//     the same number of black nodes.

class Node {
 public:
  Node(const int value, Node *parent = 0);
  virtual ~Node();

  const int value() const {return value_;}
  void set_value(const int value) {value_ = value;}

  const NodeColor color() const {return color_;}
  void set_color(const NodeColor color) {color_ = color;}

  Node *left() const {return left_;}
  void set_left(Node *left) {left_ = left;}

  Node *right() const {return right_;}
  void set_right(Node *right) {right_ = right;}

  Node *parent() const {return parent_;}
  void set_parent(Node *parent) {parent_ = parent;}

 private:
  int value_;
  NodeColor color_;
  Node *left_;
  Node *right_;
  Node *parent_;
};

enum TraverseType {
  kPrefix,
  kInfix,
  kPostfix
};

class RedBlackTree {
 public:
  RedBlackTree();
  ~RedBlackTree();

  void Add(const int value);
  Node *Find(int value) const;
  const int Min() const;
  const int Max() const;
  bool Delete(const int value);
  void Traverse(std::function<void(Node *)> callback, 
                const TraverseType type = kInfix);
  void TraverseBreath(std::function<void(Node *)> callback);
  void TraverseDepth(std::function<void(Node *)> callback);

 protected:
  void LeftRotate(Node *x);
  void RightRotate(Node *x);
  void FixColoring(Node *x);
  void FixColoringDelete(Node *x);
  void Transplant(Node *u, Node *v);
  Node *Successor(Node *n);
  void Delete(Node *node);
  void Traverse(Node *node, std::function<void(Node *)> callback, 
                const TraverseType type = kInfix);

 private:
  Node *nil_;
  Node *root_;
};

} // namespace redblack

#endif
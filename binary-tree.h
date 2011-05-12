#ifndef BINARY_H_
#define BINARY_H_

#include <functional>

namespace binarytree {

class Node {
 public:
  Node(const int value, Node *parent = 0);
  virtual ~Node();

  const int value() const {return value_;}
  void set_value(const int value) {value_ = value;}

  Node *left() const {return left_;}
  void set_left(Node *left) {left_ = left;}

  Node *right() const {return right_;}
  void set_right(Node *right) {right_ = right;}

  Node *parent() const {return parent_;}
  void set_parent(Node *parent) {parent_ = parent;}

 private:
  int value_;
  Node *left_;
  Node *right_;
  Node *parent_;
};

enum TraverseType {
  kPrefix,
  kInfix,
  kPostfix
};

class BinaryTree {
 public:
   BinaryTree();
   ~BinaryTree();

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
  Node *Min(Node *node) const;
  Node *Max(Node *node) const;
  void Transplant(Node *u, Node *v);
  Node *Successor(Node *n);
  void Delete(Node *node);
  void Traverse(Node *node, std::function<void(Node *)> callback, 
                const TraverseType type = kInfix);

 private:
  Node *root_;
};

} // namespace binarytree

#endif
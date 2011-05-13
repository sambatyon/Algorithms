#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <utility>
#include <functional>

namespace graph {

enum NodeColor {
  kWhite,
  kGray,
  kBlack
};

class Node {
 public:
  Node(int key);

  int key() const {return key_;}
  void set_key(int key) {key_ = key;}

  NodeColor color() const {return color_;}
  void set_color(NodeColor color) {color_ = color;}

  size_t predecesor() const {return predecesor_;}
  void set_predecesor(size_t predecesor) {predecesor_ = predecesor;}

  size_t distance_to_source() const {return distance_to_source_;}
  void set_distance_to_source(size_t distance) {distance_to_source_ = distance;}

 private:
  // key is equivalent to the contents of the graph. It can be
  // a pointer to an object, a process, just whatever you want
  int key_;
  NodeColor color_;
  size_t predecesor_;
  size_t distance_to_source_;
};


class Graph {
 public:
  Graph();
  // if edges contains the pair (i, j) then there is an edge between nodes[i] and
  // nodes[j]
  void Init(std::vector<Node> nodes,
            std::vector<std::pair<size_t, size_t> > edges);
  void BreathFirstSearch(size_t source, std::function<void(Node &)> callback);

 private:
  std::vector<Node> nodes_;
  std::vector<std::list<size_t> > edges_;
};
  
} // namespace graph

#endif // GRAPH_H_
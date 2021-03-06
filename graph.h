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

  size_t discovery_time() const {return discovery_time_;}
  void set_discovery_time(size_t time) {discovery_time_ = time;}

  size_t visited_time() const {return visited_time_;}
  void set_visited_time(size_t time) {visited_time_ = time;}

 private:
  // key is equivalent to the contents of the graph. It can be
  // a pointer to an object, a process, just whatever you want
  int key_;
  NodeColor color_;
  size_t predecesor_;
  size_t distance_to_source_;
  size_t discovery_time_;
  size_t visited_time_;
};


class Graph {
 public:
  static const size_t kInfinity;
  static const size_t kNil;
  Graph();
  // if edges contains the pair (i, j) then there is an edge between nodes[i] 
  // and nodes[j]
  void Init(std::vector<Node> &nodes,
            std::vector<std::pair<size_t, size_t> > &edges);
  void BreathFirstSearch(size_t source, std::function<void(Node &)> callback);
  // requires to run BreathFirstSearch before running GetPath
  std::list<size_t> GetPath(size_t from, size_t to);
  void DepthFirstSearch(std::function<void(Node &)> callback);

 private:
  void DepthFirstSearchVisit(size_t node, std::function<void(Node &)> callback,
                             unsigned *time);
  
  std::vector<Node> nodes_;
  std::vector<std::list<size_t> > edges_;
};
  
} // namespace graph

#endif // GRAPH_H_
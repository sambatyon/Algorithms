#include "graph.h"

#include <algorithm>
#include <iterator>
#include <limits>
#include <queue>

namespace graph {
  
const size_t Graph::kNil = std::numeric_limits<size_t>::max();
const size_t Graph::kInfinity = std::numeric_limits<size_t>::max();

Node::Node(int key) : key_(key),
                      color_(kWhite),
                      predecesor_(Graph::kNil),
                      distance_to_source_(Graph::kInfinity),
                      discovery_time_(Graph::kInfinity),
                      visited_time_(Graph::kInfinity) {
}

Graph::Graph() : nodes_(), edges_() {
}

void Graph::Init(std::vector<Node> &nodes,
            std::vector<std::pair<size_t, size_t> > &edges) {
  nodes_.clear();
  edges_.resize(nodes.size());
  std::vector<std::list<size_t> > *edges_ptr = &edges_;
  
  std::copy(nodes.begin(), nodes.end(), std::back_inserter(nodes_));
  std::for_each(edges.begin(), edges.end(),
      [edges_ptr](std::pair<size_t, size_t> &edge) -> void {
        (*edges_ptr)[edge.first].push_back(edge.second);
      }    
  );
  std::for_each(edges_.begin(), edges_.end(), [](std::list<size_t> &l) {
    l.sort();
  }
  );
}

void Graph::BreathFirstSearch(size_t source,
                              std::function<void(Node &)> callback) {
  std::for_each(nodes_.begin(), nodes_.end(),
                [](Node &n) -> void {
                  n.set_color(kWhite);
                  n.set_predecesor(kNil);
                  n.set_distance_to_source(kInfinity);
                }
               );

  nodes_[source].set_color(kGray);
  nodes_[source].set_predecesor(kNil);
  nodes_[source].set_distance_to_source(0);
  
  std::queue<size_t> to_visit;
  to_visit.push(source);
  while (!to_visit.empty()) {
    size_t current = to_visit.front();
    to_visit.pop();
    for (std::list<size_t>::iterator it = edges_[current].begin();
         it != edges_[current].end(); ++it) {
      if (nodes_[*it].color() == kWhite) {
        nodes_[*it].set_color(kGray);
        nodes_[*it].set_distance_to_source(nodes_[current].distance_to_source()
                                            + 1);
        nodes_[*it].set_predecesor(current);
        to_visit.push(*it);
      }
    }
    callback(nodes_[current]);
    nodes_[current].set_color(kBlack);
  }
}

std::list<size_t> Graph::GetPath(size_t from, size_t to) {
  std::list<size_t> res;
  if (from == to) {
    res.push_front(from);
    return res;
  } else if (nodes_[to].predecesor() == kNil) {
    res.push_front(kInfinity);
    return res;
  } else {
    std::list<size_t> tmp = GetPath(from, nodes_[to].predecesor());
    if (tmp.front() == kInfinity) {
      return res;
    } else {
      res.insert(res.begin(), tmp.begin(), tmp.end());
      res.push_front(to);
      return res;
    }
  }
  return std::list<size_t>();
}

void Graph::DepthFirstSearch(std::function<void(Node &)> callback) {
  std::for_each(nodes_.begin(), nodes_.end(),
                [](Node &n) -> void {
                  n.set_color(kWhite);
                  n.set_predecesor(kNil);
                  n.set_distance_to_source(kInfinity);
                });
  unsigned time = 0;
  for (size_t node = 0; node < nodes_.size(); ++node)
    if (nodes_[node].color() == kWhite)
      DepthFirstSearchVisit(node, callback, &time);
}

void Graph::DepthFirstSearchVisit(size_t node,
                                  std::function<void(Node &)> callback,
                                  unsigned *time) {
  nodes_[node].set_discovery_time((*time)++);
  nodes_[node].set_color(kGray);
  for (std::list<size_t>::iterator it = edges_[node].begin();
      it != edges_[node].end(); ++it) {
    if (nodes_[*it].color() == kWhite) {
      nodes_[*it].set_predecesor(node);
      DepthFirstSearchVisit(*it, callback, time);
    }
  }
  nodes_[node].set_color(kBlack);
  nodes_[node].set_visited_time((*time)++);
  callback(nodes_[node]);
}

  
}
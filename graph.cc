#include "graph.h"

#include <algorithm>
#include <iterator>
#include <limits>
#include <queue>

namespace graph {

Node::Node(int key) : key_(key),
                      color_(kWhite),
                      predecesor_(std::numeric_limits<size_t>::max()),
                      distance_to_source_(std::numeric_limits<size_t>::max()) {
}

Graph::Graph() : nodes_(), edges_() {
}

void Graph::Init(std::vector<Node> nodes,
            std::vector<std::pair<size_t, size_t> > edges) {
  nodes_.clear();
  edges_.resize(nodes.size());
  
  std::copy(nodes.begin(), nodes.end(), std::back_inserter(nodes_));
  std::for_each(edges.begin(), edges.end(),
      [&edges_](std::pair<size_t, size_t> &edge) -> void {
        edges_[edge.first].push_back(edge.second);
      }    
  );
}

void Graph::BreathFirstSearch(size_t source,
                              std::function<void(Node &)> callback) {
  std::for_each(nodes_.begin(), nodes_.end(),
                [](Node &n) -> void {
                  n.set_color(kWhite);
                  n.set_predecesor(std::numeric_limits<size_t>::max());
                  n.set_distance_to_source(std::numeric_limits<size_t>::max());
                }
               );

  nodes_[source].set_color(kGray);
  nodes_[source].set_predecesor(std::numeric_limits<size_t>::max());
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
      callback(nodes_[current]);
      nodes_[current].set_color(kBlack);
    }
  }
}

  
}
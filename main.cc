#include "sort.h"
#include "red-black.h"
#include "heap.h"
#include "graph.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cstdio>

void PrintVec(std::vector<int> &vec) {
  std::ostream_iterator<int> oi(std::cout, " ");
  std::copy(vec.begin(), vec.end(), oi);
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  redblack::RedBlackTree rb;
  rb.Add(5);
  rb.Add(6);
  rb.Add(7);
  rb.Add(8);
  rb.Add(9);
  rb.Add(1);
  rb.Add(2);
  rb.Add(3);
  rb.Add(4);
  rb.Add(10);
  rb.Traverse([](redblack::Node *x) -> void {std::cout << x->value() << " ";}, redblack::kPrefix);
  std::cout << std::endl;
  rb.Traverse([](redblack::Node *x) -> void {std::cout << x->value() << " ";}, redblack::kInfix);
  std::cout << std::endl;
  rb.Traverse([](redblack::Node *x) -> void {std::cout << x->value() << " ";}, redblack::kPostfix);
  std::cout << std::endl;
  rb.TraverseBreath([](redblack::Node *x) -> void {std::cout << x->value() << " ";});
  std::cout << std::endl;
  rb.TraverseDepth([](redblack::Node *x) -> void {std::cout << x->value() << " ";});

  int arr[] = {1, 3, 5, 4, 2, 7, 10, 9, 8, 6};
  std::vector<int> vec(arr, arr + 10);
  std::cout << std::endl << "Insertion sort:" << std::endl;
  InsertionSort(vec);
  PrintVec(vec);
  
  int arr1[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  std::vector<int> vec1(arr1, arr1 + 10);
  HeapSort(vec1);
  std::cout << "Heap Sort:" << std::endl;
  PrintVec(vec1);

  std::vector<int> vec2(arr1, arr1 + 10);
  std::cout << "Quick sort:" << std::endl;
  QuickSort(vec2);
  PrintVec(vec2);

  std::vector<int> vec3(arr1, arr1 + 10);
  std::cout << "Merge sort:" << std::endl;
  MergeSort(vec3);
  PrintVec(vec3);

  std::cout << std::endl << "Graphs: " << std::endl;
  std::vector<graph::Node> nodes(8, graph::Node(0));
  int i = 0;
  std::for_each(nodes.begin(), nodes.end(),
                [&i](graph::Node &n) -> void {n.set_key(i++);});
  std::vector<std::pair<size_t, size_t> > edges;
  edges.push_back(std::make_pair<size_t, size_t>(0, 1));
  edges.push_back(std::make_pair<size_t, size_t>(0, 4));
  edges.push_back(std::make_pair<size_t, size_t>(1, 0));
  edges.push_back(std::make_pair<size_t, size_t>(1, 5));
  edges.push_back(std::make_pair<size_t, size_t>(2, 3));
  edges.push_back(std::make_pair<size_t, size_t>(2, 5));
  edges.push_back(std::make_pair<size_t, size_t>(2, 6));
  edges.push_back(std::make_pair<size_t, size_t>(3, 2));
  edges.push_back(std::make_pair<size_t, size_t>(3, 6));
  edges.push_back(std::make_pair<size_t, size_t>(3, 7));
  edges.push_back(std::make_pair<size_t, size_t>(4, 0));
  edges.push_back(std::make_pair<size_t, size_t>(5, 1));
  edges.push_back(std::make_pair<size_t, size_t>(5, 2));
  edges.push_back(std::make_pair<size_t, size_t>(5, 6));
  edges.push_back(std::make_pair<size_t, size_t>(6, 2));
  edges.push_back(std::make_pair<size_t, size_t>(6, 3));
  edges.push_back(std::make_pair<size_t, size_t>(6, 5));
  edges.push_back(std::make_pair<size_t, size_t>(6, 7));
  edges.push_back(std::make_pair<size_t, size_t>(7, 6));
  edges.push_back(std::make_pair<size_t, size_t>(7, 3));
  graph::Graph graph;
  graph.Init(nodes, edges);
  graph.BreathFirstSearch(0,
      [](graph::Node &n) -> void {std::cout << n.key() << " ";});
  std::cout << std::endl;
  std::list<size_t> path = graph.GetPath(0, 7);
  if (path.front() != graph::Graph::kInfinity) {
    std::ostream_iterator<size_t> oi(std::cout, " ");
    std::copy(path.begin(), path.end(), oi);
    std::cout << std::endl;
  } else {
    std::cout << "Path does not exist" << std::endl;
  }
  graph.DepthFirstSearch([](graph::Node &n) -> void {
    std::printf("key: %d\n\tdisc: %d\n\tvis: %d\n", n.key(), n.discovery_time(),
                n.visited_time());
  });
  
  return 0;
}


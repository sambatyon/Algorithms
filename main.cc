#include "sort.h"
#include "red-black.h"
#include "heap.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

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

	return 0;
}


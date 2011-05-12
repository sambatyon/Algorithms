#include "sort.h"

#include <algorithm>

void InsertionSort(std::vector<int> &vec) {
  for (int curr_index = 1; curr_index < vec.size(); ++curr_index) {
    int current = vec[curr_index];
    int insert_index = curr_index - 1;
    while (insert_index >= 0 && vec[insert_index] > current) {
      vec[insert_index + 1] = vec[insert_index];
      --insert_index;
    }
    vec[insert_index + 1] = current;
  }
}

namespace {
int Parent(int i) {return i >> 1;}
int Left(int i) {return (i << 1) + 1;}
int Right(int i) {return (i << 1) + 2;}

void Heapify(std::vector<int> &vec, int position, int heap_size) {
  int left = Left(position);
  int right = Right(position);
  int largest;
  if (left < heap_size && vec[left] > vec[position])
    largest = left;
  else
    largest = position;
  if (right < heap_size && vec[right] > vec[largest])
    largest = right;
  if (largest != position) {
    std::swap(vec[position], vec[largest]);
    Heapify(vec, largest, heap_size);
  }
}
}

void HeapSort(std::vector<int> &vec) {
  int heap_size = vec.size();
  for (int i = vec.size() / 2; i >= 0; --i)
    Heapify(vec, i, heap_size);
  for (int i = vec.size() - 1; i >= 1; --i) {
    std::swap(vec[0], vec[i]);
    --heap_size;
    Heapify(vec, 0, heap_size);
  }
}

namespace {
void QuickSort(std::vector<int> &vec, int begin, int end) {
  if (begin >= end)
    return;
  int pivot = vec[end];
  int i = begin - 1;
  for (int j = begin; j < end; ++j)
    if (vec[j] <= pivot)
      std::swap(vec[++i], vec[j]);
  std::swap(vec[++i], vec[end]);
  QuickSort(vec, begin, i - 1);
  QuickSort(vec, i + 1, end);
}
}

void QuickSort(std::vector<int> &vec) {
  QuickSort(vec, 0, vec.size() - 1);
}

namespace {
void Merge(std::vector<int> &vec, int begin, int middle, int end) {
  std::vector<int> first(vec.begin() + begin, vec.begin() + middle + 1);
  std::vector<int> second(vec.begin() + middle + 1, vec.begin() + end + 1);

  first.push_back(std::numeric_limits<int>::max());
  second.push_back(std::numeric_limits<int>::max());
  int i = 0;
  int j = 0;
  for (int k = begin; k <= end; ++k) 
    if (first[i] < second[j])
      vec[k] = first[i++];
    else
      vec[k] = second[j++];
}

void MergeSort(std::vector<int> &vec, int begin, int end) {
  if (begin < end) {
    int middle = (begin + end) / 2;
    MergeSort(vec, begin, middle);
    MergeSort(vec, middle + 1, end);
    Merge(vec, begin, middle, end);
  }
}
}

void MergeSort(std::vector<int> &vec) {
  MergeSort(vec, 0, vec.size() - 1);
}
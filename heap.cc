#include "heap.h"

#include <algorithm>
#include <limits>

Heap::Heap() : vec_(), size_(0) {
}

Heap::~Heap() {
}

void Heap::Heapify(int i) {
  int left = Left(i);
  int right = Right(i);
  int largest;
  if (left < size_ && vec_[left] > vec_[i])
    largest = left;
  else
    largest = i;
  if (right < size_ && vec_[right] > vec_[largest])
    largest = right;
  if (largest != i) {
    std::swap(vec_[i], vec_[largest]);
    Heapify(largest);
  }
}

int Heap::Max() const {
  if (size_ > 0)
    return vec_[0];
  else
    return std::numeric_limits<int>::min();
}

int Heap::ExtractMax() {
  if (size_ <= 0)
    return std::numeric_limits<int>::min();
  int max = vec_[0];
  vec_[0] = vec_[--size_];
  Heapify(0);
  return max;
}

bool Heap::IncreasePriority(int i, int new_priority) {
  if (new_priority < vec_[i])
    return false;
  vec_[i] = new_priority;
  while (i > 0 && vec_[Parent(i)] < vec_[i]) {
    std::swap(vec_[Parent(i)], vec_[i]);
    i = Parent(i);
  }
  return true;
}

void Heap::Insert(int i) {
  if (size_ == vec_.size())
    vec_.push_back(std::numeric_limits<int>::min());
  else
    vec_[size_] = std::numeric_limits<int>::min();
  ++size_;
  IncreasePriority(size_ - 1, i);
}
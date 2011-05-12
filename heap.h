#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

class Heap {
 public:
  static int Parent(int i) {return i >> 1;}
  static int Left(int i) {return (i << 1) + 1;}
  static int Right(int i) {return (i << 1) + 2;}

  Heap();
  ~Heap();

  int size() const {return size_;}
  int Max() const;
  int ExtractMax();
  // returns true if the priority was successfully increased
  bool IncreasePriority(int i, int new_priority);
  void Insert(int i);

 private:
  void Heapify(int i);

  std::vector<int> vec_;
  int size_;
};

#endif
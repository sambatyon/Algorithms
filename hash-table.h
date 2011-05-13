#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <string>
#include <vector>
#include <list>

// provides following operations:
// - Put
// - Get
// - Has
// - Delete
// - Values
// - Keys
// - Count
// - Capacity

class HashTable {
 public:
  explicit HashTable(const unsigned capacity = 10);
  virtual ~HashTable();

  void PutValue(std::string key, const int value);
  int GetValue(std::string key) const;
  bool Contains(std::string key) const;
  void Delete(std::string key);
  std::vector<std::string> GetKeys() const;
  std::vector<int> GetValues() const;

  unsigned count() const {return count_;}
  unsigned capacity() const {return container_.size();}
  // only works for increasing the capacity
  void set_capacity(unsigned capacity);

 private:
  unsigned Hash(std::string key) const;
  std::vector<std::list<std::pair<std::string, int> > > container_;
  unsigned count_;
};

#endif // SIMPLE_HASH_TABLE_H_
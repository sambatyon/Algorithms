#include "hash-table.h"

#include <utility>
#include <limits>
#include <algorithm>

typedef std::pair<std::string, int> entry;
typedef std::list<entry> entry_list;
typedef std::vector<entry_list> container_type;

HashTable::HashTable(const unsigned capacity) 
    : container_(capacity),
      count_(0) {
}

HashTable::~HashTable(){
}

void HashTable::PutValue(std::string key, const int value) {
  int hash = Hash(key);
  // if the element is already there, just update its value
  for (entry_list::iterator it = container_[hash].begin();
      it != container_[hash].end(); ++it) {
    if (it->first == key) {
      it->second = value;
      return;
    }
  }
  container_[hash].push_back(std::make_pair(key, value));
  count_++;
  // It is getting too crowded so we increase the size
  if (count_ > 1.61803399 * container_.size())
    set_capacity(2 * container_.size());
}

int HashTable::GetValue(std::string key) const {
  int hash = Hash(key);
  for (entry_list::const_iterator it = container_[hash].begin();
      it != container_[hash].end(); ++it) {
    if (it->first == key)
      return it->second;
  }
  return std::numeric_limits<int>::min();
}

bool HashTable::Contains(std::string key) const {
  int hash = Hash(key);
  for (entry_list::const_iterator it = container_[hash].begin();
      it != container_[hash].end(); ++it) {
    if (it->first == key)
      return true;
  }
  return false;
}

void HashTable::Delete(std::string key) {
  int hash = Hash(key);
  for (entry_list::const_iterator it = container_[hash].begin();
      it != container_[hash].end(); ++it) {
    if (it->first == key) {
      container_[hash].erase(it);
      --count_;
    }
  }
}

std::vector<std::string> HashTable::GetKeys() const {
  std::vector<std::string> res;
  for (container_type::const_iterator it = container_.begin();
      it != container_.end(); ++it) {
    for (std::list<std::pair<std::string, int> >::const_iterator list_it = it->begin();
         list_it != it->end(); ++list_it)
      res.push_back(list_it->first);
  }
  return res;
}

std::vector<int> HashTable::GetValues() const {
  std::vector<int> res;
  for (container_type::const_iterator it = container_.begin();
      it != container_.end(); ++it) {
    for (entry_list::const_iterator list_it = it->begin();
         list_it != it->end(); ++list_it)
      res.push_back(list_it->second);
  }
  return res;
}

void HashTable::set_capacity(unsigned capacity) {
  // collect all elements.
  // reset all list
  std::list<std::pair<std::string, int> > entries;
  for (container_type::iterator it = container_.begin();
      it != container_.end(); ++it) {
    for (entry_list::iterator list_it = it->begin();
         list_it != it->end(); ++list_it)
      entries.push_back(std::make_pair(list_it->first, list_it->second));
    it->clear();
  }
  // resize
  container_.resize(capacity);
  // put all elements back
  while (!entries.empty()) {
    std::pair<std::string, int> current = entries.front();
    entries.pop_front();
    PutValue(current.first, current.second);
  }
}

unsigned HashTable::Hash(std::string key) const {
  unsigned hash = 0;
  for (int i = 0; i < key.size(); ++i)
    hash = ((31 * hash) % capacity()) 
        + (static_cast<unsigned>(key.at(i)) % capacity());
  return hash % capacity();
}
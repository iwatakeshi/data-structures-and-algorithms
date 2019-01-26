#ifndef HASHMAP_H
#define HASHMAP_H
#include "doublylinkedlist.hpp"
#include <utility>
#include <functional>

template<typename T, typename U>
class HashMap {
private:
  DoublyLinkedList<std::pair<T, U>> * table_ = nullptr;

  unsigned long long hash(T key) {
    std::hash<T> _;
    return _(key);
  }
public:
  HashMap() {
    table_ = new DoublyLinkedList<std::pair<T, U>>();
    cout << hash("Hello") << endl;
  }

  void set(T key, U value) {

  }

  ~HashMap() {
    delete table_;
  }
};


#endif
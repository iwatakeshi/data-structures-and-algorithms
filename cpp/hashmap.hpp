#ifndef HASHMAP_H
#define HASHMAP_H
#include "doublylinkedlist.hpp"
#include <utility>

template<typename T, typename U>
class HashMap{
private:
  DoublyLinkedList<std::pair<T, U>> * table_ = nullptr;

  unsigned long long hash(unsigned key) {
    
  }
public:
  HashMap() {
    table_ = new DoublyLinkedList();
  }

  void set(T key, U value) {

  }

  ~HashMap() {
    delete table_;
  }
};


#endif
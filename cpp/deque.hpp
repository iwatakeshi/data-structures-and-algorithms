#ifndef DEQUE_H
#define DEQUE_H
#include "doublylinkedlist.hpp"

template <class T>
class Deque {

private:
DoublyLinkedList<T> * list;

public:

Deque() {
  list = new DoublyLinkedList<T> ();
}

~Deque() {
  delete list;
}

T at(uint64_t index) {
  return list->at(index);
}

void push_front(T value) {
  list->add_head(value);
}

void push_back(T value) {
  list->add_tail(value);
}

T pop_front() {
  auto value = list->at(0);
  list->remove_head();
  return value;
}

T pop_back() {
  auto value = list->at(size() - 1);
  list->remove_tail();
  return value;
}

T front() {
  return at(0)
}

T back() {
  return at(size() - 1);
}

uint64_t size() {
  return list->length();
}

bool is_empty() {
  return list->is_empty();
}

};

#endif
#ifndef QUEUE_H
#define QUEUE_H
#include "doublylinkedlist.hpp"

template <class T>
class Queue {

private:
DoublyLinkedList<T> * list;

public:

Queue() {
  list = new DoublyLinkedList<T> ();
}

~Queue() {
  delete list;
}

T at(unsigned long long index) {
  return list->at(index);
}

void push(T value) {
  list->add_tail(value);
}

T pop() {
  auto value = list->at(0);
  list->remove_head();
  return value;
}

T front() {
  return at(0)
}

T back() {
  return at(size() - 1);
}

unsigned long long size() {
  return list->length();
}

bool is_empty() {
  return list->is_empty();
}

};

#endif
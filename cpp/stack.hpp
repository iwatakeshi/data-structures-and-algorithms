#ifndef STACK_H
#define STACK_H
#include "doublylinkedlist.hpp"

template <class T>
class Stack {

private:
DoublyLinkedList<T> * list;

public:

Stack() {
  list = new DoublyLinkedList<T> ();
}

~Stack() {
  delete list;
}

T at(unsigned long long index) {
  return list->at(index);
}

void push(T value) {
  list->add_tail(value);
}

T pop() {
  auto value = list->at(list->count() - 1);
  list->remove_tail();
  return value;
}

T front() {
  return at(0);
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
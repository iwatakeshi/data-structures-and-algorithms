#ifndef DOUBLYLIKNEDLIST_H
#define DOUBLYLIKNEDLIST_H

#include "node.hpp"
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class DoublyLinkedList {

private:
Node<T> * head_;
Node<T> * tail_;
unsigned long long count_;
public:
DoublyLinkedList() {
  head_= nullptr;
  tail_ = nullptr;
  count_ = 0;
}

~DoublyLinkedList() {
  count_ = 0;
  for (long long i = 0; i < count_; i++) {
    remove(i);
  }
  delete head_;
  delete tail_;
}

/**
 * Return the number of items in the list.
 */
unsigned long long count() {
  return count_;
}

/**
 * Return the value at the specified index.
 */
T at (unsigned long long index) {
  if (index < 0 || index > count_) {
    return nullptr;
  }

  auto *node = head_;

  for(long long i = 0; i < index; i++) {
    node = node->get_next();
  }

  return node->get_value();
}

/**
 * Add a value at the beginning
 */
void add_head(T value) {
  auto * node = new Node<T>(value);

  if (count_ == 0) {
    head_ = node;
    tail_ = head_;
    count_ += 1;
    return;
  }

  // [new head] -> [old head]
  node->set_next(head_);
  // [new head] <- [old head]
  head_->set_previous(node);
  head_ = node;

  count_ += 1;
}

/**
 * Add a value to the end
 */
void add_tail(T value) {
  auto *node = new Node<T>(value);

  if (count_ == 0) {
    return add_head(value);
  }
  // [old tail]-> [new tail]
  tail_->set_next(node);
  // [old tail] <- [new tail]
  node->set_previous(tail_);
  // Node becomes new tail
  tail_ = node;

  count_ += 1;
}

/**
 * Add a value at the specified index.
 */
void add(long long index, T value) {
  
  if (index == 0) {
    return add_head(value);
  }

  if (index >= count_) {
    return add_tail(value);
  }

  auto * current = head_;

  auto * node = new Node<T>(value);

  for (unsigned long long i = 0; i < index - 1; i++) {
    current = current->get_next();
  }

  auto * next = current->get_next();
  
  node->set_next(next);
  node->set_previous(current);

  current->set_next(node);
  next->set_previous(node);

  count_ += 1;

}

/**
 * Remove a value at the beginnning
 */
void remove_head() {
  if (count_ == 0) {
    return;
  }

  auto * node = head_;
  head_ = head_->get_next();

  delete node;

  count_ -= 1;

  if (count_ == 0) {
    auto * node = tail_;
    tail_ = nullptr;
    delete node;
  }
}

/**
 * Remove a value at the end.
 */
void remove_tail() {
  if (count_ == 0) {
    return;
  }

  if (count_ == 1) {
    return remove_head();
  }

  auto * previous = tail_->get_previous();
  previous->remove_next();
  tail_ = previous;

  count_ -= 1;
}

void remove(long long index) {
  if (index < 0 || index >= count_) {
    return;
  }

  if (count_ == 1 || index == 0) {
    return remove_head();
  }

  if (index == count_ - 1) {
    return remove_tail();
  }

  auto *current = head_;

  for (long long i = 0; i < index - 1; i++) {
    current = current->get_next();
  }

  auto * node = current->get_next();
  auto * next = node->get_next();
  
  current->set_next(next);
  next->set_previous(current);

  delete node;

  count_ -= 1;
}

/**
 * Return the index of a value.
 */
long long index_of(T value) {
  if (count_ == 0) {
    return -1;
  }

  if (head_->get_value() == value) {
    return 0;
  }

  if (tail_->get_value() == value) {
    return count_ - 1;
  }

  auto * current = head_;

  for(long long i = 0; i < count_; i++) {
    if (current && current->get_value() == value) {
      return i;
    }
    current = current->get_next();
  }

  return -1;
}

};

#endif
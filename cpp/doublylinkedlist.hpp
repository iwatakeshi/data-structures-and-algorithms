#ifndef DOUBLYLIKNEDLIST_H
#define DOUBLYLIKNEDLIST_H

#include "node.hpp"
#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

template <class T>
class DoublyLinkedList {

private:
Node<T> * head_ = nullptr;
Node<T> * tail_ = nullptr;
unsigned long long count_ = 0;

Node<T> *merge_sort(Node<T> *head){
  if (!head || !head->get_next())
      return head;
  Node<T> *second = split(head);

  // Recur for left and right halves
  head = merge_sort(head);
  second = merge_sort(second);

  // Merge the two sorted halves
  return merge(head, second);
}

Node<T> *split(Node<T> *head) {
  Node<T> *fast = head, *slow = head;
  while (fast->get_next() && fast->get_next()->get_next()) {
      fast = fast->get_next()->get_next();
      slow = slow->get_next();
  }
  Node<T> *temp = slow->get_next();
  slow->remove_next();
  return temp;
}

Node<T> *merge(Node<T> *first, Node<T> *second) {
  // If first linked list is empty
  if (!first)
      return second;

  // If second linked list is empty
  if (!second)
      return first;

  // Pick the smaller value
  if (first->get_value() < second->get_value()) {
    first->set_next(merge(first->get_next(), second));
    first->get_next()->set_previous(first);
    first->remove_previous();
    return first;
  }
  else {
    second->set_next(merge(first, second->get_next()));
    second->get_next()->set_previous(second);
    second->remove_previous();
    return second;
  }
}

public:

~DoublyLinkedList() {
  Node<T> * t = tail_;
  while(t != nullptr) {
    Node<T> * t2 = t;
    t = t->get_previous();
    delete t2;
  }
  head_ = nullptr;
  tail_ = nullptr;
  count_ = 0;
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
    return NULL;
  }

  auto *node = head_;

  for(long long i = 0; i < index; i++) {
    node = node->get_next();
  }

  return node->get_value();
}

/**
 * Set the value at the specified index.
 */
void at(unsigned long long index, T value) {
  if (index < 0 || index > count_) {
    return NULL;
  }

  auto *node = head_;

  for (long long i = 0; i < index; i++) {
    node = node->get_next();
  }
  node->set_value(value);
}

/**
 * Add a value at the beginning.
 */
void add_head(T value) {
  auto * node = new Node<T>(value);
  if (count_ == 0 && head_ == nullptr) {
    head_ = node;
    tail_ = node;
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
 * Add a value to the end.
 */
void add_tail(T value) {
  auto *node = new Node<T>(value);

  if (count_ == 0 && tail_ == nullptr) {
    delete node;
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
void add(unsigned long long index, T value) {
  
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
 * Remove a value at the beginnning.
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
/**
 * Sort the list.
 */
void sort() {
  head_ = merge_sort(head_);
  auto * node = head_;
  while (node->has_next()) {
    node = node->get_next();
  }

  tail_ = node;
}

};

#endif
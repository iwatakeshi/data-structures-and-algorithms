#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.hpp"
#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

template <class T>
class LinkedList {
private:
  Node<T> *head_;
  Node<T> *tail_;
  uint64_t length_;

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
    return first;
  }
  else {
    second->set_next(merge(first, second->get_next()));
    return second;
  }
}

public:
  LinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
  }
  
  ~LinkedList() {
    auto * h = head_;
    while (h != nullptr) {
      auto * next = h->get_next();
      delete h;
      h = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
  }

  /**
   * Return the number of items in the list.
   */
  uint64_t length () {
    return length_;
  }

  bool is_empty() {
    return length_ == 0;
  }

  /**
   * Return the value at the specified index.
   */
  T at(uint64_t index) {
    if (index < 0 || index > length_) {
      return NULL;
    }

    auto *node = head_;

    for (long long i = 0; i < index; i++) {
      node = node->get_next();
    }
    return node->get_value();
  }

  /**
   * Set the value at the specified index.
   */
  void at(uint64_t index, T value) {
    if (index < 0 || index > length_) {
      return;
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

    if (length_ == 0) {
      head_ = node;
      tail_ = head_;
      length_ += 1;
      return;
    }

    node->set_next(head_);
    head_ = node;
    length_ += 1;
  }

  /**
   * Add a value at the end.
   */
  void add_tail(T value) {
    auto *node = new Node<T>(value);

    if (length_ == 0) {
      delete node;
      add_head(value);
      return;
    }

    tail_->set_next(node);
    tail_ = node;

    length_ += 1;
  }

  /**
   * Add a value at the specified index.
   */

  void add(long long index, T value) {
    if (index == 0) {
      return add_head(value);
    }
    
    if (index >= length_) {
      return add_tail(value);
    }

    auto *current = head_;
    for (uint64_t i = 0; i < index - 1; i++) {
      current = current->get_next();
    }

    auto *node = new Node<T>(value);

    // The new node will point to the next node
    node->set_next(current->get_next());

    current->set_next(node);
    length_ += 1;
  }

  /**
   * Remove a value at the beginning.
   */
  void remove_head() {
    if (length_ == 0) {
      return;
    }

    auto * node = head_;

    head_ = head_->get_next();

    delete node;
    length_ -= 1;

    if (length_ == 0) {
      auto *node = tail_;
      tail_ = nullptr;
      delete node;
    }
  }

  /**
   * Remove a value at the end.
   */

  void remove_tail() {
    if (length_ == 0) {
      return;
    }

    if (length_ == 1) {
      return remove_head();
    }

    // Our cursor in the list
    auto *current = head_;
    // Node to remove from list
    auto *node = tail_;

    // Traverse the list until we are right before the end
    while(current->get_next() != node) {
        current = current->get_next();
    }
    // Set the tail right before the end
    tail_ = current;
    // Remove the link to the next node
    tail_->remove_next();

    delete node;

    length_ -= 1;
  }

  void remove(uint64_t index) {
    if (index < 0 || index >= length_) {
      return;
    }

    if (length_ == 1 || index == 0) {
      return remove_head();
    }

    if (index == length_ - 1) {
      return remove_tail();
    }
    
    auto *current = head_;

    for (long long i = 0; i < index - 1; i++) {
      current = current->get_next();
    }

    auto * node = current->get_next();
    auto * next = node->get_next();

    current->set_next(next);
    node->remove_next();

    delete node;

    length_ -= 1;
  }

  /**
   * Return the index of a value.
   */
  long long index_of(T value) {
    if (length_ == 0) {
      return -1;
    }

    if (head_->get_value() == value) {
      return 0;
    }

    if (tail_->get_value() == value) {
      return length_ - 1;
    }

    auto * current = head_;
    for (long long i = 0; i < length_; i++) {
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
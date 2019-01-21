#ifndef NODE_HPP
#define NODE_HPP
#include <cstddef>
template <class T>
class Node {
private:
  Node<T> * previous_;
  Node<T> * next_;
  T value_;
public:
  Node() {
    next_ = nullptr;
    previous_ = nullptr;
    value_ = NULL;
  }
  Node(T value) {
    value_ = value;
  }

  ~Node() {
    if (next_) {
     remove_next();
    }

    if (previous_) {
      remove_previous();
    }

    if (value_) {
      value_ = NULL;
    }
  }

   Node<T>* get_previous() {
     return previous_;
   }

   void set_previous(Node<T> * node) {
     previous_ = node;
   }

   void remove_previous() {
     previous_ = nullptr;
   }
   
   Node<T>* get_next() {
     return next_;
   }

   void set_next(Node<T> * node) {
     next_ = node;
   }

   void remove_next() {
     next_ = nullptr;
   }
 
   T get_value() {
     return value_;
   }

   void set_value(T value) {
     value_ = value;
   }
};

#endif
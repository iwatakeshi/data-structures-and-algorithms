#ifndef NODE_HPP
#define NODE_HPP
template <class T>
class Node {
private:
  Node<T> * previous_;
  Node<T> * next_;
  T value_;
public:
  Node() {
    next_ = nullptr;
    value_ = nullptr;
  }
  Node(T value) {
    value_ = value;
  }
  ~Node() {

    if (previous_) {
      previous_ = nullptr;
    }

    if (next_) {
      next_ = nullptr;
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
};

#endif
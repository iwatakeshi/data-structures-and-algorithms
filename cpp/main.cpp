#include "doublylinkedlist.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {

  // auto * stack = new Stack<string>();

  // stack->push("Hello");
  // stack->push("world");
  // stack->push("how");
  // stack->push("are");
  // stack->push("you?");

  // stack->pop();
  // stack->push("youuuu!");
  auto * list = new DoublyLinkedList<int>();
  list->add_tail(24);
  list->add_tail(423);
  list->add_tail(2);
  list->add_tail(5);
  list->sort();

  for (int i = 0; i < list->count(); i++) {
    cout << list->at(i) << " " << i << endl;
  }

  delete list;

  return 0;
}
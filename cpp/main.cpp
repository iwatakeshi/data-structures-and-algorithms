#include "stack.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {

  auto * stack = new Stack<string>();

  stack->push("Hello");
  stack->push("world");
  stack->push("how");
  stack->push("are");
  stack->push("you?");

  stack->pop();
  stack->push("youuuu!");

  for (int i = 0; i < stack->size(); i++) {
    cout << stack->at(i) << " " << i << endl;
  }

  delete stack;

  return 0;
}
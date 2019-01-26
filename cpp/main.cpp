#include "linkedlist.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main() {

  // auto* map = new HashMap<string, string>();

  auto * list = new LinkedList<int>();
  list->add_tail(24);
  list->add_tail(423);
  list->add_tail(2);
  list->add_tail(5);

  list->add(1, 100);
  list->sort();

  for (int i = 0; i < list->count(); i++) {
    cout << i << ": " << list->at(i) << endl;
  }

  delete list;

  return 0;
}
// #include "linkedlist.hpp"
#include "array.hpp"
#include <string>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;
using std::string;

int main() {

  // auto* map = new HashMap<string, string>();

  // auto * list = new LinkedList<int>();
  // list->add_tail(24);
  // list->add_tail(423);
  // list->add_tail(2);
  // list->add_tail(5);

  // list->add(1, 100);
  // list->sort();

  // for (int i = 0; i < list->count(); i++) {
  //   cout << i << ": " << list->at(i) << endl;
  // }

  // delete list;

  Array<int> a;
  for(int i = 0; i < 50; i++) {
    a.push(i);
  }
  auto b = a.filter([] (int x) {
    return x % 2 == 0;
  });

  b.for_each([](auto x, auto i) {
    cout << i << ": " << x << endl;
  });

  return 0;
}
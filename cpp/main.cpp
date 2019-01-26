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
  a.push(1);
  a.push(2);
  auto b = a.map<int>([] (int x) {
    return x * 2;
  });

  b.for_each([](auto x, auto i) {
    cout << i << ": " << x << endl;
  });

  return 0;
}
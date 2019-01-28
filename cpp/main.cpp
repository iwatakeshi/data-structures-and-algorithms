// #include "linkedlist.hpp"
#include "array.hpp"
#include "utils/bench.hpp"
#include <iostream>
#include <functional>
#include <string>

using std::cout;
using std::endl;
using std::function;
using std::string;

void test(uint64_t i, function<void(uint64_t)> const& lambda) {
  for (uint64_t j = 1; j < i * 10000; j++) {
    lambda(j);
  }
}

void print_test(string name, uint64_t index) {
  cout << name << " - " << std::to_string(index * 10000) << " " << "elements" << endl;
}

void print_time(double time) {
  cout << "time: " << std::to_string(time) << endl;
  cout << endl;
}

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

  for (auto i = 1; i <= 10; i++) {
    Array<int> a;
    double duration = 0.0;

    print_test("push", i);

    duration = Bench::time([&] () {
      test(i, [&] (uint64_t j) {
        a.push(j);
      });
    });

    print_time(duration);
  }

  // Array<int> a;

  // a.push(1);
  // a.push(2);
  // a.push(3);

  // a.unshift(4);
  // a.shift();
  // a *= 2;

  // a.for_each([](auto x, auto i) {
  //   cout << x << " " << i << endl;
  // });

  // return 0;
}
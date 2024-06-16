#include <ctime>
#include <iostream>

#include "skiplist/skiplist.h"

int main() {
  // set random seed
  srand((unsigned)time(nullptr));

  SkipList<int, int> skiplist;
  std::cout << "-------------------Test Insert-------------------\n";
  skiplist.insert(1, 1);
  skiplist.insert(2, 2);
  skiplist.insert(3, 3);
  skiplist.insert(4, 4);
  skiplist.insert(5, 5);
  skiplist.insert(6, 6);

  std::cout << "-------------------Test Pass-------------------\n";

  std::cout << "-------------------Test Find-------------------\n";
  std::cout << "skiplist.find(1)->value_:" << skiplist.find(1)->value_ << "\n";

  std::cout << "-------------------Test Pass-------------------\n";

  std::cout << "-------------------Test Display-------------------\n";
  skiplist.display();

  std::cout << "-------------------Test Pass-------------------\n";

  std::cout << "-------------------Test Erase-------------------\n";
  skiplist.erase(4);
  skiplist.display();
  std::cout << "-------------------Test Pass-------------------\n";

  std::cout << "-------------------Test Clear-------------------\n";
  skiplist.clear();
  skiplist.display();
  std::cout << "-------------------Test Pass-------------------\n";
}

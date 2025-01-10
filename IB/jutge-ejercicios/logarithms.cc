#include <iostream>

int main() {
  int base;
  int number;
  int copy;
  while (std::cin >> base >> number) {
    int result = 1;
    copy = base;
    if (base <= number) {
      while (copy < number) {
        if (!(copy * base > number)) {
          result++;
        }
        copy = copy * base;
      }
    }
    else {
      result = 0;
    }
    std::cout << result << std::endl;
  }

  return 0;
}

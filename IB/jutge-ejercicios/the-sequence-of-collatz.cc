#include <iostream>

int main() {
  int number;
  while (std::cin >> number) {
    int count = 0;
    while (number > 1) {
      if (number % 2 == 0) {
        number /= 2;
      }
      else {
        number = number * 3 + 1;
      }
      count ++;
    }
    std::cout << count << std::endl;
  }

  return 0;
}

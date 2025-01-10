#include <iostream>

int main() {
  int number;
  int power;
  while (std::cin >> number >> power) {
    int result = 1;
    if (power != 0)  {
      for (int i = 0; i < power; i++) {
        result *= number;
      }
    }
    std::cout << result << std::endl;
  }

  return 0;
}

#include <iostream>

int main() {
  int number;
  std::cin >> number;
  if (number >= 0) {
    for (int i = 0; i <= number; i++) {
      std::cout << i << std::endl;
    }
  }
  else {
    for (int i = 0; i >= number; i--) {
      std::cout << i << std::endl;
    }
  }
  return 0;
}

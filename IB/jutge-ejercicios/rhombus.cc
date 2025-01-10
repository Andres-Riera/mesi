#include <iostream>

int main() {
  int number;
  int a {1};
  std::cin >> number;
  for (int i = 1; i <= number * 2; i+= 2) {
    for (int j = a; j < number; j++) {
      std::cout << " ";
    }
    for (int j = 1; j <= i; j++){
      std::cout << "*";
    }
    std::cout << std::endl;
    a++;
  }
  for (int i = number - 1; i > 0; i--) {
    for (int j = number; j > i; j--) {
      std::cout << " ";
    }
    for (int j = 1; j <= 2 * i - 1; j++) {
      std::cout << "*";
    }
    std::cout << std::endl;
  }

  return 0;
}

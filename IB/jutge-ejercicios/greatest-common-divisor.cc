#include <iostream>

int main() {
  int number;
  int number2;
  std::cin >> number >> number2;
  std::cout << "The gcd of " << number << " and " << number2 << " is ";
  while (number2 != 0) {
    int temp = number2;
    number2 = number % number2;
    number = temp;
  }
  int gcd = number;
  std::cout << gcd << "." << std::endl;

  return 0;
}

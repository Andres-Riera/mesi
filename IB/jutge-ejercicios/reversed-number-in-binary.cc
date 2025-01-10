#include <iostream>


int main() {
  int decimal;
  std::cin >> decimal;
  int binary;
  if (decimal == 0) {
      std::cout << decimal << std::endl;
      return 1;
  }
  while (decimal >= 1) {
    binary = decimal % 2;
    std::cout << binary;
    decimal /= 2;
  }
  std::cout << std::endl;
  
  return 0;
}

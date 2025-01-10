#include <iostream>

int main() {
  int number;
  std::cin >> number;
  int zero {0};
  std::cout << zero;
  for (int i = 1; i <= number; i++) {
     std::cout << "," << i * i * i;
  }
  std::cout << std::endl;
  
  return 0;
}

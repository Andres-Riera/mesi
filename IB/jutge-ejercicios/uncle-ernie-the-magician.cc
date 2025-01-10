#include <iostream>
#include <cmath>

int main() {
  int number;
  while (std::cin >> number){
    number /= 5;
    number -= 9;
    number /= 4;
    number -= 6;
    number /= 5;
    std::cout << number<< std::endl;
  }
  return 0;
}

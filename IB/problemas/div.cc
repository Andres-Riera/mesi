#include <iostream>

int main(){
  int number1 {0};
  int number2 {0};
  std::cin >> number1 >> number2;
  int number3 {number1 / number2};
  std::cout << number3 << " " << number1 - number3 * number2 << std::endl;
  return 0;
}

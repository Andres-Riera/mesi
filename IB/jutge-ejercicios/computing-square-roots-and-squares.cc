#include <iostream>
#include <cmath>
#include <iomanip>

void Power(double number) {
  number = static_cast<int>(number);
  std::cout << std::fixed << std::setprecision(0) << pow(number,2) << " ";
}

void Root(int number) {
  std::cout << std::fixed << std::setprecision(6) << sqrt(number) << std::endl;
}

int main() {
  double number;
  while(std::cin >> number) {
  Power(number);
  Root(number);
  }
  return 0;
}

#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  double number;
  while (std::cin >> number) {
    double radian = number * M_PI / 180;
    std::cout << std::fixed << std::setprecision(6) << sin(radian) << " " << cos(radian) << std::endl;
  }
  return 0;
}

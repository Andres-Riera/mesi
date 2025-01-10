#include <iostream>
#include <vector>
#include <iomanip>

int main() {
  double x;
  std::cin >> x;
  double value;
  double sum {0};
  while (std::cin >> value) {
    sum = sum * x + value;
  }
  std::cout << std::fixed << std::setprecision(4) << sum << std::endl;
  
  return 0;
}

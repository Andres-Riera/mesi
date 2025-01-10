#include <iostream>
#include <iomanip>

int main() {
  double number; 
  double number_two;
  while (std::cin >> number >> number_two) {
    double sum{0};
    for (int i = number_two + 1; i <= number; i++) {
      sum = sum + 1.0 / i;
    }
    std::cout << std::fixed << std::setprecision(10) << sum << std::endl;
  }
  
  return 0;
}

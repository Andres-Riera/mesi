#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
  double x;
  std::cin >> x;
  double value;
  std::vector<double> function;
  while (std::cin >> value) {
    function.push_back(value);
  }
  double sum {function[0]};
  for (int i = 1; i < function.size(); i++) {
    if (function [i] != 0) {
      sum = sum + function[i] * pow(x, i);
    }
  }
  std::cout << std::fixed << std::setprecision(4) << sum << std::endl;
  
  return 0;
}

#include <iostream>

bool AreEqual(const double number1, const double number2, const double epsilon = 1e-7) {
  if (abs(number1 - number2) < epsilon) {
  return true;
  } 
  return false;
}

int main() {
  double a, b;
  std::cin >> a >> b;
  std::cout << AreEqual(a, b);
  return 0;
}

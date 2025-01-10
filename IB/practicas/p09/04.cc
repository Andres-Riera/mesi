#include <iostream>

double ApproximateRoot(const int number, const double epsilon = 1.0e-4) {
  double root {1.0};
  double delta {1.0};
  while (number - root * root > epsilon) {
    if (delta > 0) {
      while (root * root < number) {
        root += delta;
      }
    }
    else {
      while (root * root > number) {
        root -= delta;
      }
    }
    delta = delta * -0.5;
  }
  return root;
}

int main() {
  double number;
  std::cin >> number;
  std::cout << ApproximateRoot(number) << std::endl;
  return 0;
}

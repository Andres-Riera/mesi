#include <iostream>

void Sum(int number, int& sum) {
  for (int i = 1; i <= number; i++) {
    sum = sum + i * i;
  }
}


int main() {
  int number;
  std::cin >> number;
  int sum {0};
  Sum(number, sum);
  std::cout << sum << std::endl;
  return 0;
}

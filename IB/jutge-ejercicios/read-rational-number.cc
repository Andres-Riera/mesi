#include <iostream>
#include <algorithm>
#include <numeric>

void read_rational(int& num, int& den) {
  char auxiliar;
  std::cin >> num >> auxiliar >> den;
  int gcd = std::gcd(num, den);
  num = num / gcd;
  den = den /gcd;
}

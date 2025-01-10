#include <iostream>
#include <numeric>

bool read_rational(int& num, int& den) {
  char auxiliar;
  if (std::cin >> num >> auxiliar >> den) {
    int gcd = std::gcd(num, den);
    num = num / gcd;
    den = den /gcd;
    return true;
  }
  return false;
 }

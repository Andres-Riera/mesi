#include <iostream>

int main() {
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  if (c < a && d >= b || c <= a && d > b) {
    std::cout << "1" << std::endl;
  }
  else if (a < c && b >= d || a <= c && b > d) {
    std::cout << "2" << std::endl;
  }
  else if (a == c && b == d) {
    std::cout << "=" << std::endl;
  }
  else {
    std::cout << "?" << std::endl;
  }
  return 0;
}

#include <iostream>

int main() {
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  if (c < a && d >= b || c <= a && d > b) {
    std::cout << "1";
  }
  else if (a < c && b >= d || a <= c && b > d) {
    std::cout << "2";
  }
  else if (a == c && b == d) {
    std::cout << "=";
  }
  else {
    std::cout << "?";
  }
  std::cout << " , ";
  if (c > a) {
  int temp = a;
  a = c;
  c = temp;
  }
  if (d < b) {
  int temp = b;
  b = d;
  d = temp;
  }
  if (a > b) {
  std::cout << "[]" << std::endl;
  return 0;
  }
  std::cout << "[" << a << "," << b << "]" << std::endl;
  return 0;
}

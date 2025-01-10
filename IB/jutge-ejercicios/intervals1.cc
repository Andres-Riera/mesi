#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main() {
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
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

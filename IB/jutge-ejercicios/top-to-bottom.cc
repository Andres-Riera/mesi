#include <iostream>

void Order(int& x, int& y) {
  if (y > x) {
    int temp = x;
    x = y;
    y = temp;
  }
}

int main() {
  int x;
  int y;
  std::cin >> x >> y;
  Order(x, y);
  for (int i = x; i >= y; i--) {
    std::cout << i << std::endl;
  }
}

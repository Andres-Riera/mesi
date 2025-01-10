#include <iostream>

int main() {
  int a;
  int b;
  std::cin >> a >> b;
  for (int i = a; i <=b; i++) {
    std::cout << i;
    if (i < b) {
      std::cout << ",";
    }
  }
  std::cout << std::endl;
  return 0;
}

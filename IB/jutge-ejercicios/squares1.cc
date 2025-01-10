#include <iostream>

int main() {
  int n;
  bool first = true;
  while (std::cin >> n) {
    if (first) {
      first = false;
    } else {
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << n;
        if (j == n - 1) {
          std::cout << std::endl;
        }
      }
    }
  }
  return 0;
}


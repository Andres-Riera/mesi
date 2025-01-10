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
    int count = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << count;
        count++;
        if (count > 9) {
            count = 0;
        }
        if (j == n - 1) {
          std::cout << std::endl;
        }
      }
    }
  }
  return 0;
}

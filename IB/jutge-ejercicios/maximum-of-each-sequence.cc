#include <iostream>

int main() {
  int numbers;
  while (std::cin >> numbers) {
    int value;
    int max;
    for (int i = 0; i < numbers; i++) {
      std::cin >> value;
      if (i == 0) {
         max = value; 
      }
      if (value > max) {
        max = value;
      }
    }
    std::cout << max << std::endl;
  }

  return 0;
}

#include <iostream>
#include <vector>

int main() {
  int terms;
  while (std::cin >> terms) {
    std::vector<int> vector = {};
    for (int i = 0; i < terms; i++) {
      int number;
      std::cin >> number;
      vector.push_back(number);
    }
    for (int i = terms - 1; i >= 0; i--) {
      if (i != 0) {
        std::cout << vector[i] << " ";
      }
      else {
        std::cout << vector[i];
      }
    }
    std::cout << std::endl;
  }
  return 0;
}

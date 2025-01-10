#include <iostream>
#include <string>

int main() {
  std::string words;
  std::string firstword;
  std::cin >> firstword;
  int max {1};
  int consecutives {1};
  while (std::cin >> words) {
    if (words == firstword) {
      consecutives++;
      if (consecutives >= max) {
        max = consecutives;
      }
    }
    else {
      consecutives = 0;
    }
  }
  std::cout << max << std::endl;

  return 0;
}

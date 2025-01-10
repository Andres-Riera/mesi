#include <iostream>
#include <string>

int main() {
  int rows;
  int columns;
  std::cin >> rows >> columns;
  int coins {0};
  std::string number;
  bool white = 1;
  for (int i = 0; i < rows; i++) {
    std::cin >> number;
    for (int j = 0; j < columns; j++) {
      if (white) {
        coins += static_cast<int>(number[j]) - 48;
      }
      white = !white;
    }
    if (columns != 1) {
      white = !white;
    }
  }
  std::cout << coins << std::endl;

  return 0;
}

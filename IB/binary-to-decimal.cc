#include <iostream>

int main() {
  int binary;
  std::cin >> binary;
  int copy = binary;
  int digits {0};
  while (copy >= 1) {
    if (copy % 10 > 1) {
      std::cout << "Wrong Input" << std::endl;
      return 1;
    }
    copy /= 10;
    digits += 1;
  }
  int decimal {0};
  int j = 1;
  for (int i = 1; j <= digits; i = i * 2) {
    decimal = decimal + (binary % 10) * i;
    binary /= 10;
    j++;
  }
  std::cout << decimal << std::endl;


  return 0;
}

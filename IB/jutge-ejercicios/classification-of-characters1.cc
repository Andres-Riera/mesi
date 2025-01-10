#include <iostream>

int main() {
  char letter;
  std::cin >> letter;
  int number {static_cast<int>(letter)};
  if (number <= 90) {
    std::cout << "uppercase" << std::endl;
  }
  else {
    std::cout << "lowercase" << std::endl;
  }
  if (number > 90) {
    number -= 32;
  }
  switch (number) {
    case 65:
    case 69:
    case 73:
    case 79:
    case 85:
      std::cout << "vowel" << std::endl;
      break;
    default:
      std::cout << "consonant" << std::endl;
      break;
  }

  return 0;
}

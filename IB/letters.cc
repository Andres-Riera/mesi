#include <iostream>

int main() {
  char letter;
  int other_letter;
  std::cin >> letter;
  other_letter = static_cast<int>(letter);
  if (other_letter > 90) {
    other_letter = other_letter - 32;
  }
  else {
    other_letter = other_letter + 32;
  }
  std::cout << static_cast<char>(other_letter) << std::endl;

  return 0;
}

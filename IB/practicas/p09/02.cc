#include <string>
#include <iostream>

int main() {
  std::string word;
  std::cin >> word;
  for (int i = 0; i < word.size(); i++) {
    int letter = static_cast<int>(word[i]);
    switch (letter) {
      case 97:
      case 101:
      case 105:
      case 111:
      case 117:
        word[i] = static_cast<char>(letter - 32);
      default:
        break;
    }
  }
  std::cout << word << std::endl;

  return 0;
}

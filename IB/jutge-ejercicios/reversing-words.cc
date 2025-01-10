#include <iostream>
#include <string>

int main() {
  std::string word;
  while (std::cin >> word) {
    for (int i = word.size() - 1; i >= 0; i--) {
      std::cout << word[i];
    }
    std::cout << std::endl;
  }
  return 0;
}

#include <iostream>
#include <string>

int main() {
  std::string word;
  std::string word2;
  std::cin >> word >> word2;
  if (word < word2) {
    std::cout << word << " < " << word2 << std::endl;
  }
  else if (word > word2) {
    std::cout << word << " > " << word2 << std::endl;
  }
  else {
    std::cout << word << " = " << word2 << std::endl;
  }

  return 0;
}

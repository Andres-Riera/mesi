#include <iostream>
#include <vector>
#include <string>

int main() {
  int times;
  std::string word;
  std::vector<std::string> words;
  std::cin >> times;
  for (int i = 0; i < times; i++) {
    std::cin >> word;
    words.push_back(word);
  }
  for (int i = words.size() - 1; i >= 0; i--) {
      word = words[i];
      for (int j = word.size() - 1; j >= 0; j--) {
        std::cout << word[j];
      }
      std::cout << std::endl;
  }
  return 0;
}

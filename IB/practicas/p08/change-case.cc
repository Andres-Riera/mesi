#include <iostream>
#include <string>

void CaseConverter(std::string& word) {
  for (int i = 0; i < word.size(); i++) {
    int letter = static_cast<int>(word[i]);
    if (letter < 91 && letter > 64) {
      word[i] = static_cast<char>(letter + 32);
    }
    else if (letter < 123 && letter > 96) {
      word[i] = static_cast<char>(letter - 32);
    }
  }   
}

int main() {
  std::string word;
  std::cin >> word;
  CaseConverter(word);
  std::cout << word << std::endl;
  return 0;
}

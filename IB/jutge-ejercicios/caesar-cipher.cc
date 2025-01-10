#include <iostream>
#include <string>

int main() {
  int number; 
  std::string phrase;
  while (std::cin >> number){
    while (number >= 26) {
      number = number - 26;
    }
    std::cin >> phrase;
    for (int i = 0; i < phrase.size() - 1; i++) {
      int letter = static_cast<int>(phrase[i]);
      if (letter > 96 && letter < 123) {
        letter = letter - 32 + number;
        while (letter > 90) {
          letter = letter - 26;
        }
        phrase[i] = static_cast<char>(letter);
      }
      if (phrase[i] != '_') {
      std::cout << phrase[i];
      }
      else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  return 0;
}

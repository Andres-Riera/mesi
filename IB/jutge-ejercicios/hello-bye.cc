#include <iostream>
#include <string>

int main() {
  std::string str;
  std::cin >> str;
  for (int i = 0; i < str.size(); i++) {
  if (str[i] == 'h') {
    if (str[i + 1] == 'e') {
      if (str[i + 2] == 'l') {
        if (str[i + 3] == 'l') {
          if (str[i + 4] == 'o') {
            std::cout << "hello" << std::endl;
            return 0;
          }
        }
      }
    }
  }
  }
  std::cout << "bye" << std::endl;

  return 0;
}

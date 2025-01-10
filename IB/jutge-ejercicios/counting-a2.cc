#include <iostream>
#include <string>

int main() {
  std::string str;
  std::getline(std::cin, str);
  int count {0};
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '.') {
      break;
    }
    if (str[i] == 'a') {
      count = count + 1;
    }
  }
  std::cout << count << std::endl;

  return 0;
}

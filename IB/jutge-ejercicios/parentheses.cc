#include <iostream>
#include <string>

int main() {
  
  std::string str;
  std::cin >> str;
  int count_open {0};
  int count_closed {0};
  if (str.size() > 0 && str[0] == '(' && str.size() % 2 == 0) {
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '(') {
        count_open++;
      }
      else {
        count_closed++;
      }
      if (count_closed > count_open) {
        std::cout << "no" << std::endl;
        return 0;
      }
    }
    if (count_open == count_closed) {
      std::cout << "yes" << std::endl;
    }
    else {
      std::cout << "no" << std::endl;
    }
  } 
  else if (str.size() == 0) {
    std::cout << "yes" << std::endl;
   }
  else {
    std::cout << "no" << std::endl;
  }

  return 0;
}

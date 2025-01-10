#include <iostream>
#include <string.h>

int main() {
  std::string str;
  std::cin >> str;
  int x {0};
  int y {0};
  for (int i = 0; i < str.size(); i++) {
    switch (str[i]) {
        case 's': 
            y = y + 1;
            break;
        case 'n': 
            y = y - 1;
            break;
        case 'e': 
            x = x + 1;
            break;
        case 'w': 
            x = x - 1;
            break;
    }
  }
  std::cout << "(" << x << "," << " " << y << ")" << std::endl;
  
  return 0;
}

#include <iostream>
#include <string.h>
#include <algorithm>

int main() {
  std::string number;
  std::cin >> number;
  reverse (number.begin(), number.end());
  std::cout << number << std::endl;
  
  return 0;
}

#include <iostream>
#include <vector>

int main() {
  int number;
  while (std::cin >> number) {
    if (number > 9) {
      while (number > 9) {
        std::cout << "The product of the digits of " << number << " is ";
        std::vector<int> digits;
        int copy = number;
        while (copy > 0) {
          digits.push_back(copy % 10);
          copy /= 10;
        }
        int result = 1;
        for (int i = 0; i < digits.size();  i++) {    
          result = result * digits [i];
        }
        std::cout << result << "." << std::endl;
        number = result;
        digits.clear();
      }
      std::cout << "----------" << std::endl;
    }
    else {
      std::cout << "The product of the digits of " << number << " is " 
                << number << "." << std::endl;
      std::cout << "----------" << std::endl;
    }
  }

  return 0;
}

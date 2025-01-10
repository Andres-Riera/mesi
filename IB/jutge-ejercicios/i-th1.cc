#include <iostream>
#include <vector>

int main() {

  int position;
  std::cin >> position;
  int value;
  std::vector<int> numbers;
  while (std::cin >> value) {
    numbers.push_back(value);
  }
  std::cout << "At the position " << position << " there is a(n) " 
	    << numbers[position - 1] << "." << std::endl;
    
  return 0;
}

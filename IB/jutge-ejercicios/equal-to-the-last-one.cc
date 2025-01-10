#include <iostream>
#include <vector>

int main() {

  int size;
  std::cin >> size;
  int numbers[size] {};
  for (int i = 0; i < size; i++) {
    std::cin >> numbers[i];
  };
  int count {0};
  for (int i = 0; i < size - 1; i++) {
    if (numbers[i] == numbers[size - 1]) {
      count++;
    }
  }
  std::cout << count << std::endl;
  
  return 0;
}

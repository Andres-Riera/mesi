#include <iostream>
#include <vector>

int main() {
  int length {};
  std::cin >> length;
  int vector [length] {};
  for (int i=0 ; i < length ; i++) {
      std::cin >> vector [i];
  }
  for (int i=length - 1 ; i >= 0; i--){
    std::cout << vector [i] << " ";
  }
  std::cout << std::endl;
    return 0;
}

#include <iostream>

int main() {
  int temperature;
  std::cin >> temperature;
  if (temperature > 30) {
    std::cout << "it's hot" << std::endl;
    if (temperature >= 100) {
      std::cout << "water would boil" << std::endl;
    }
  }
  else if (temperature < 10) {
    std::cout << "it's cold" << std::endl;
    if (temperature <= 0) {
      std::cout << "water would freeze" << std::endl;
    }
  }
  else {
    std::cout << "it's ok" << std::endl;
  }
  
  return 0;
}

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main() {
  int times;
  std::cin >> times;
  for (int i = 0; i < times; i++) {
    std::string form;
    std::cin >> form;
    if (form == "rectangle") {
      double width;
      double length;
      std::cin >>  width >> length;
      std::cout << std::fixed << std::setprecision(6) << width * length;
    }
    else {
      double radio;
      std::cin >> radio;
      std::cout << std::fixed << std::setprecision(6) << radio * radio * M_PI;
    }
    std::cout << std::endl;
  }
  
  return 0;
}

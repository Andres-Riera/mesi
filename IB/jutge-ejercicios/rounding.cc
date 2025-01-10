#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
  double x;
  std::cin >> x;
  std::cout << std::fixed << std::setprecision(0) << floor (x) << " " 
            << ceil(x) << " " << round (x) << std::endl;

  return 0;
}

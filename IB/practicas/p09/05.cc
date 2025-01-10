#include <cmath>
#include <iostream>

int Hipotenusa(const int cateto1, const int cateto2) {
  double hipotenusa = sqrt(cateto1 * cateto1 + cateto2 * cateto2);
  return hipotenusa;
}

int main() {
  int cateto1;
  int cateto2;
  std::cin >> cateto1 >> cateto2;
  std::cout << Hipotenusa(cateto1, cateto2) << std::endl;
  return 0;
}

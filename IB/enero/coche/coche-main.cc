#include "coche.h"

int main() {
  Car coche;
  Car coche2;
  std::cin >> coche >> coche2;
  if (coche > coche2) {
    std::cout << "coche 1 tiene más kms que coche 2\n";
  } else {
    std::cout << "coche 2 tiene más kms que coche 1\n";
  }
  return 0;
}
#include "racionales.h"

int main() {
  Racional a{1, 2};
  Racional b{1, 4};
  a.print();
  std::cout << " ";
  b.print();
  Racional c = a.suma(b);
  std::cout << " ";
  c.print();
  return 0;
}
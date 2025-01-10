#include "book.h"

int main(int argc, char* argv[]) {
  double impuesto{std::stoi(argv[1])};
  Book quijote{"El quijote", 1605, 10.0, impuesto};
  std::cout << quijote << std::endl;
  return 0;
}
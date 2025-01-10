#include "case.h"

int main(int argc, char* argv[]) {
  std::string palabra{argv[1]};
  Switch(palabra);
  std::cout << palabra << std::endl;
  return 0;
}
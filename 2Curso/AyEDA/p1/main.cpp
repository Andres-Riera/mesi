#include <fstream>

#include "BigUnsigned.hpp"
#include "BigInteger.hpp"

BigInteger mcd(BigInteger num1, BigInteger num2) {
  if (num2 == BigInteger(0)) {
    return num1;
  } else {
    return mcd(num2, num1 % num2);
  }
}


int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  BigInteger num1;
  BigInteger num2;
  file >> num1 >> num2;
  std::cout << "Operando 1: " << num1 << std::endl;
  std::cout << "Operando 2: " << num2 << std::endl;
  std::cout << "Suma: " << num1 + num2 << std::endl;
  std::cout << "Resta: " << num1 - num2 << std::endl;
  std::cout << "Multiplicación: " << num1 * num2 << std::endl;
  std::cout << "División: " << num1 / num2 << std::endl;
  std::cout << "Resto: " << num1 % num2 << std::endl;
  std::cout << "MCD: " << mcd(num1, num2) << std::endl;
  return 0;
}
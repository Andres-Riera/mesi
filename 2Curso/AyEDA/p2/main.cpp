#include <fstream>
#include <iostream>
#include <string>
#include "BigUnsignedPlantila.hpp"
#include "BigIntegerPlantilla.hpp"
#include "BigRationalPlantilla.hpp"

template <unsigned char Base>
void Operaciones(const BigRational<Base>& num1, const BigRational<Base>& num2) {
  std::cout << "Base: " << static_cast<int>(Base) << std::endl;
  std::cout << "N1 = " << num1 << std::endl;
  std::cout << "N2 = " << num2 << std::endl;
  std::cout << "N1 < N2: ";
  if (num1 < num2 ? std::cout << "true" : std::cout << "false");
  std::cout << std::endl;
  std::cout << "N1 == N2: ";
  if (num1 == num2 ? std::cout << "true" : std::cout << "false");
  std::cout << std::endl;
  std::cout << "Suma: " << num1 + num2 << std::endl;
  std::cout << "Resta: " << num1 - num2 << std::endl;
  std::cout << "Multiplicación: " << num1 * num2 << std::endl;
  std::cout << "División: " << num1 / num2 << std::endl;
}

template <unsigned char Base>
void ProcesarArchivo(std::ifstream& file) {
  std::string trash;
  std::string number1num_str, number1den_str, number2num_str, number2den_str;
  BigUnsigned<Base> num1den, num2den;
  BigInteger<Base> num1num, num2num;
  file >> trash >> trash >> number1num_str >> trash >> number1den_str;
  file >> trash >> trash >> number2num_str >> trash >> number2den_str;
  BigInteger<Base> tempBigInteger(reinterpret_cast<const unsigned char*>(number1num_str.c_str()));
  num1num = tempBigInteger;
  BigInteger<Base> tempBigInteger2(reinterpret_cast<const unsigned char*>(number2num_str.c_str()));
  num2num = tempBigInteger2;
  BigUnsigned<Base> tempBigUnsigned(reinterpret_cast<const unsigned char*>(number1den_str.c_str()));
  num1den = tempBigUnsigned;
  BigUnsigned<Base> tempBigUnsigned2(reinterpret_cast<const unsigned char*>(number2den_str.c_str()));
  num2den = tempBigUnsigned2;
  BigRational<Base> num1 {num1num, num1den};
  BigRational<Base> num2 {num2num, num2den};
  Operaciones(num1, num2);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero>" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "No se pudo abrir el archivo: " << argv[1] << std::endl;
    return 1;
  }
  std::string trash;
  int base;
  file >> trash >> trash >> base;
  if (base == 2) {
    ProcesarArchivo<2>(file);
  } else if (base == 8) {
    ProcesarArchivo<8>(file);
  } else if (base == 10) {
    ProcesarArchivo<10>(file);
  } else if (base == 16) {
    ProcesarArchivo<16>(file);
  } else {
    std::cerr << "Base no soportada." << std::endl;
    return 1;
  }
  file.close();
  return 0;
}
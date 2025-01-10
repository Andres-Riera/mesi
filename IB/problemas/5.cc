#include <iostream>

int main() {
  double primer_valor {};
  double segundo_valor {};
  double tercer_valor {};
  double cuarto_valor {};
  std::cout << "Primer valor: ";
  std::cin >> primer_valor;
  std::cout << "Segundo valor: ";
  std::cin >> segundo_valor;
  std::cout << "Tercer valor: ";
  std::cin >> tercer_valor;
  std::cout << "Cuarto valor: ";
  std::cin >> cuarto_valor;
  double media {(primer_valor + segundo_valor + tercer_valor + cuarto_valor) / 4};
  std::cout << "La media es: " << media << std::endl;
  return 0;
 }

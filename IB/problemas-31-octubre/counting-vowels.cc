/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 30 Oct 2023 
  * @brief This program reads a string and returns the number of vowels it has
  * @bug There are no known bugs
  */

#include <iostream>
#include <string>

int CountVowels(const std::string& text, int& vowels) {
  for (int i = 0; i < text.size(); i++) {
    int letter = static_cast<int>(text [i]);
    if (letter > 90) {
      letter -= 32;
    }
    switch (letter) {
      case 65:
      case 69:
      case 73:
      case 79:
      case 85:
        vowels++;
    }
  }
  std::cout << vowels; /*Las funciones no deberían de hacer más de una cosa,
                         pero en este caso la función cuenta el número de 
                         vocales y lo imprime */
  return 0;
}
int main() {
  std::string text;
  std::getline(std::cin, text);
  int vowels {0};
  CountVowels(text, vowels);
  std::cout << std::endl;

  return 0;
}

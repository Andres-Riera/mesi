/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 30 Oct 2023 
  * @brief This program reads a string and a letter and prints the first
           position of the letter starting at 0, and if it is not in the 
           string, the program will print -1
  * @bug There are no known bugs
  */

#include <iostream>
#include <string>

void FirstPosition(const std::string& text, const char letter, int& position) {
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == letter) {
      position = i;
      break;
    }
  }
}

int main() {
  std::string text;
  char letter;
  std::cin >> text >> letter;
  int position {-1};
  FirstPosition(text, letter, position);
  std::cout << position << std::endl;

  return 0;
}

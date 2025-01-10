/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file  P90615_maximum.cc
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 25 Oct 2023
  * @brief This program reads three integer number and prints the higher one
  * @bug There are no known bugs
  * @see https://jutge.org/problems/P90615_en
  */

#include <iostream>

int main() {
  int number_one;
  int number_two; 
  int number_three;
  std::cin >> number_one >> number_two >> number_three;
  if (number_one > number_two && number_one > number_three ) {
    std::cout << number_one << std::endl;
  }
  else if (number_two > number_one && number_two > number_three ) {
    std::cout << number_two << std::endl;
  }
  else {
    std::cout << number_three << std::endl;
  }
  
  return 0;
}

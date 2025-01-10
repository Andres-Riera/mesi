/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file 
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 
  * @brief 
  * @bug There are no known bugs
  * @see 
  */

#include <iostream>

int main() {
  int years {};
  int days {};
  int hours {};
  int minutes {};
  int seconds {};
  
  std::cin >> years >> days >> hours >> minutes >> seconds;
  std::cout << years*365*86400 + days*86400 + hours*3600 + minutes*60 + seconds << std::endl;

  return 0;
}

/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 30 Oct 2023 
  * @brief This program reads a number n and prints the first n integer right 
           triangles
  * @bug There are no known bugs
  */

#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n < 1) {
    std::cout << "Wrong parameter" << std::endl; 
    return 0;
  }
  int a {3};
  for (int i = 0; i < n; i++) {
    int b;
    int c;
    int k;  
    if (a % 2 != 0) {
      k = (a - 1) / 2;
      b = 2 * k * (k + 1);
      c = b + 1;
    }
    else {
      k = a / 2;
      b =  k * k - 1;
      c = k * k + 1;
    }
    if (a <= b && b <= c) {
      std::cout << a << " " << b << " " << c << std::endl;
    }
    a++;
  }
  return 0;
}

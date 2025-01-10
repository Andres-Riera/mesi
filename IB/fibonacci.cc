/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file fibonacci.cc
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 23 Oct 2023
  * @brief This program prints the first n Fibonacci terms
  * @bug There are no known bugs
  */

#include <iostream>
#include <vector>

int main() {
    int numbers;
    std::cin >> numbers;
    std::vector<int> vector;
    vector.push_back(0);
    if (numbers > 1) {
        vector.push_back(1);
    }
    for (int i = 2; i < numbers; i++) {
        int next_number = vector[i - 1] + vector[i - 2];
        vector.push_back(next_number);
    }
    for (int i = 0; i < numbers; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

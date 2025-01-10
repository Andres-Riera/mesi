/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file increasin-pairs.cc 
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 26 Oct 2023
  * @brief This program reads sequences of natural numbers, and that for each 
           one prints the number of pairs of consecutive numbers such that the 
           second number of the pair is greater than the first one
  * @bug There are no known bugs
  * @see https://jutge.org/problems/P73501_en
  */

#include <iostream>

int main() {
    int cycle;
    std::cin >> cycle;
    int value;
    int past;
    int sum {0};
    int j {-1};
    for (int i = 0; i < cycle; i ++) {
        if (value == 0) {
		past = 0;
	}
	while (std::cin >> value && value != 0) {
		j++;
		if (value > past && j > 0) {
                	sum = sum + 1;
         	}
            	past = value;
        }
        std::cout << sum << std::endl;
        sum = 0;
	j = -1;
    }

    return 0;
}

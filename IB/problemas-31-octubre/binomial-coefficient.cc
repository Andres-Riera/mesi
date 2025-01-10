/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @author Andrés David Riera Rivera alu0101618654@ull.edu.es
  * @date 30 Oct 2023 
  * @brief This program reads n and k integer numbers and prints the binomial
           coefficient of them
  * @bug When n >= 13 the result is incorrect
  */

#include <iostream>

void BinomialCoefficient(int n, int k, int& result) {
  int nfactorial {1};
  for (int i = 1; i <= n; i++) {
    nfactorial *= i;
  }
  int kfactorial {1};
  for (int i = 1; i <= k; i++) {
    kfactorial *= i;
  }
  int nkfactorial {1};
  for (int i = 1; i <= n - k; i++) {
    nkfactorial *= i;
  }
  result = nfactorial / (kfactorial * nkfactorial);
}

bool CheckCorrectParameters(int n, int k) {
  if (n < 0 || k <= 0 || k > n) {
    return false;
  }
  else {
    return true;
  }
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  int result {0};
  if (!CheckCorrectParameters(n, k)) {
    std::cout << "Wrong parameters" << std::endl;
    return 0;
  }
  BinomialCoefficient(n, k, result);
  std::cout << result << std::endl;
  return 0;
}

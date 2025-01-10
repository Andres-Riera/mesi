#include <iostream>
#include <vector>
#include <iomanip>

int main() {
  std::vector<double> vector;
  double value;
  while (std::cin >> value) {
    vector.push_back(value);
  }
  double suma;
  for (int i = 0; i < vector.size(); i++) {
    suma = suma + vector [i];
  }
  std::cout << std::fixed << std::setprecision(2) << suma / vector.size() << std::endl;
  return 0;
}

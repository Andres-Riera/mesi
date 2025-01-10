#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::vector<double> numbers;
    int m;
    std::cin >> m;
    for (int j = 0; j < m; j++) {
      double number;
      std::cin >> number;
      numbers.push_back(number);
    }
    std::sort(numbers.begin(), numbers.end());
    std::cout << std::fixed << std::setprecision(4) << numbers[0] << " " << numbers.back();
    double sum = 0;
    for (int j = 0; j < m; j++) {
      sum += numbers[j];
    }
    std::cout << " " << std::fixed << std::setprecision(4) << sum / m << std::endl;
  }

  return 0;
}

#include <iostream>
#include <vector>

int main() {
  int number;
  while (std::cin >> number){
  std::vector<int> vector = {};
  for (int i = 0; i < number; i++) {
    int value;
    std::cin >> value;
    vector.push_back(value);
  }
  for (int i = 0; i < vector.size(); i++) {
    int sum = 0;
    for (int j = 0; j < vector.size(); j++) {
      if (j != i) {
        sum += vector[j];
      }
    }
    if (vector[i] == sum) {
      std::cout << "YES" << std::endl;
      break;
    }
    else if (i == vector.size() - 1) {
      std::cout << "NO" << std::endl;
      break;
    }
  }
  }
  return 0;
}

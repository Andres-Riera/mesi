#include <iostream>
#include <vector>

void count_and_add(int& num, int& sum) {
  int n;
  num = 0;
  sum = 0;
  std::vector<int> numbers;
  while (std::cin >> n) {
    num++;
    numbers.push_back(n);
  }
  for (int i = 0; i < numbers.size(); i++) {
    sum += numbers[i];
  }
}

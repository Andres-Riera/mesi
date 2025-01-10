#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n;
  while (std::cin >> n) {
    std::vector<int> numbers(n - 1);
    int missing;
    for (int i = 0; i < n - 1; i++) {
      std::cin >> numbers[i];
    }
    std::sort(numbers.begin(), numbers.end());
    for (int i = 1; i <= n; i++) {
      if (!std::binary_search(numbers.begin(), numbers.end(), i)) {
        missing = i;
        break;
      }
    }
    std::cout << missing << std::endl;
  }

  return 0;
}

#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  int coins {0};
  int j = n - 1;
  for (int i = 0; i < n; i++) {
    std::string number;
    std::cin >> number;
    if (i != j) {
      coins += static_cast<int>(number[i] - 48) + static_cast<int>(number[j] - 48);
    }
    else {
      coins += static_cast<int>(number[i] - 48);
    }
    j--;
  }
  std::cout << coins << std::endl;

  return 0;
}

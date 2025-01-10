#include <iostream>
#include <cstdlib>
#include <ctime>

int Random(int number1, int number2) {
  std::srand(std::time(nullptr));
  int random = number1 +  std::rand() / ((RAND_MAX + 1u) / number2);
  return random;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << Random(a, b);

  return 0;
}

#include <cmath>

int sum_divisors(int n) {
  int sum {0};
  int sqrt_n = std::sqrt(n);

  for (int i = 1; i <= sqrt_n; i++) {
    if (n % i == 0) {
      sum += i;
      if (i != sqrt_n) {
        sum += n / i;
      }
    }
  }
  return sum;
}

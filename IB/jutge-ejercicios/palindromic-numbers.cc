#include <cmath>

bool is_palindromic(int n) {
  int copy = n;
  int i {0};
  while (copy > 9) {
    i++;
    copy /= 10;
  }
  int reversed {0};
  copy = n;
  for (i; i >= 0; i--) {
    reversed = reversed + (copy % 10) * pow(10, i);
    copy /= 10;
  }
  if (n == reversed) {
    return true;
  }
  return false;
}

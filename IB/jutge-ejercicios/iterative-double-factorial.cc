#include <iostream>

int double_factorial(int number) {
  int result;
  if (number != 0) {
    result = number;
  } else {
    return 1;
  }
  for (int i = number - 2; i > 0; i-= 2) {
    result *= i;
  }
  return result;
}

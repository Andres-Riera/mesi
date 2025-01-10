#include <iostream>

void decompose(int n, int& h, int&m, int& s) {
  h = 0;
  m = 0;
  while (n >= 3600) {
    h++;
    n -= 3600;
  }
  while (n >= 60) {
    m++;
    n -= 60;
  }
  s = n;
}

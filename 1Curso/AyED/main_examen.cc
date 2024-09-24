#include <iostream>

#include "vector_t.h"
#include "matrix_t.hpp"
#include "sll_t.h"
#include "sparse_vector_t.h"

using namespace std;

int Digitos(int x) {
  if (x == 0) {
    return 0;
  } else {
    return (1 + Digitos(x / 10));
  }
}

int main() {
  int x;
  cin >> x;
  cout << Digitos(x) << endl;
  return 0;
}
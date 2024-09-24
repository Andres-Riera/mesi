#include "racionales.h"

Racional::Racional(int num, int den) {
  assert(den != 0);
  num_ = num;
  den_ = den;
  simplificar();
}
void Racional::print() {
  std::cout << get_num() << "/" << get_den();
}

Racional Racional::suma(const Racional& fraccion) {
  return Racional(num_ * fraccion.get_den() + den_ * fraccion.get_num(), den_ * fraccion.get_den());
}

Racional Racional::resta(const Racional& fraccion) {
  return Racional(num_ * fraccion.get_den() - den_ * fraccion.get_num(), den_ * fraccion.get_den());
}

Racional Racional::multiplicacion(const Racional& fraccion) {
  return Racional(num_ * fraccion.get_num(), den_ * fraccion.get_num());
}

int Racional::gcd(int a, int b) {
  if (b == 0){
    return a;
  } else {
    return gcd(b, a % b);
  }
}
void Racional::simplificar() {
  int mcd = gcd(num_, den_);
  num_ /= mcd;
  den_ /= mcd;
}
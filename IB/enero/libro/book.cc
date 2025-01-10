#include "book.h"

double Impuesto(double precio, double impuesto) {
  return precio + precio * impuesto / 100.0;
}

std::ostream& operator<<(std::ostream& out, Book libro) {
  std::cout << libro.titulo_ << ", " << libro.year_ << ", " << libro.precio_ << ", " << Impuesto(libro.precio_, libro.impuesto_);
  return out;
}
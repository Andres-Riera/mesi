#include <iostream>
#include <cstdlib>  // Para std::rand y std::srand
#include <ctime>    // Para std::time (semilla aleatoria)

class nif {
 public:
  nif() {
    std::srand(std::time(0));
    value = 10000000 + (std::rand() % 90000000);
  }

  nif(long v) : value(v) {
    if (v < 10000000 || v > 99999999) {
      throw std::invalid_argument("El NIF debe ser un número de 8 dígitos.");
    }
  }

  bool operator==(const nif& other) const { return value == other.value; }
  bool operator!=(const nif& other) const { return value != other.value; }
  bool operator<(const nif& other) const { return value < other.value; }
  bool operator>(const nif& other) const { return value > other.value; }
  bool operator<=(const nif& other) const { return value <= other.value; }
  bool operator>=(const nif& other) const { return value >= other.value; }
  nif& operator/=(int other) { value /= other; return *this; }

  operator int() const { return static_cast<int>(value); }
  long getValue() const { return value; }
 
 private:
  long value;
};
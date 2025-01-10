#include "coche.h"

std::istream& operator>>(std::istream& in, Car& car) {
  std::string modelo;
  std::string placa;
  int kilometros;
  in >> modelo >> placa >> kilometros;
  car.SetModel(modelo);
  car.SetPlate(placa);
  car.SetKilometers(kilometros);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Car& car) {
  out << car.model() << ", " << car.plate() << ", " << car.kilometers();
  return out;
}
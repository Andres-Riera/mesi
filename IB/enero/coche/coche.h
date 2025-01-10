#ifndef COCHE_H
#define COCHE_H

#include <iostream>
#include <string>

class Car {
 public:
  Car() : model_{"Messi"}, plate_{10}, kilometers_{0} { }
  Car(std::string modelo, std::string placa, int kilometros) : model_{modelo}, plate_{placa}, kilometers_{kilometros} { }
  std::string model() const { return model_; }
  std::string plate() const { return plate_; }
  int kilometers() const { return kilometers_; }
  bool operator>(Car coche2) {
    return kilometers_ > coche2.kilometers_;
  }
  void SetModel(std::string model) { model_ = model; }
  void SetPlate(std::string plate) { plate_ = plate; }
  void SetKilometers(int kilometers) { kilometers_ = kilometers; }

 private:
  std::string model_;
  std::string plate_;
  int kilometers_;
};

std::istream& operator>>(std::istream& in, Car& car);
std::ostream& operator<<(std::ostream& out, const Car& car);


#endif
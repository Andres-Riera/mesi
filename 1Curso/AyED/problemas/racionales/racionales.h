#include <iostream>
#include <cassert>

class Racional{
 public: 
  Racional() : num_{1}, den_{1} {}
  Racional(int num, int den);
  ~Racional() {}
  int get_num() const { return num_;}
  int get_den() const { return den_;}
  void print(void);
  Racional suma(const Racional& fraccion);
  Racional resta(const Racional& fraccion);
  Racional multiplicacion(const Racional& fraccion);
 private:
  int num_;
  int den_;
  int gcd(int a, int b);
  void simplificar();
};
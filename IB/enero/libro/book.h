#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

class Book{
 public: 
  Book() : titulo_{"Don Quijote de la Mancha"}, year_{1605}, precio_{10.0}, impuesto_{1.0} { }
  Book(std::string titulo, int year, double precio, double impuesto) : titulo_{titulo}, year_{year}, precio_{precio}, 
                                                                       impuesto_{impuesto} { }
  double Impuesto(double precio, double impuesto);
  friend std::ostream& operator<<(std::ostream& out, Book libro);
 private:
  std::string titulo_;
  int year_;
  double precio_;
  double impuesto_;
};

#endif
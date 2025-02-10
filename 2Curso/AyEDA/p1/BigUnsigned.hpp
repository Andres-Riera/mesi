#pragma once

#include <iostream>
#include <vector>

class BigUnsigned{
 public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* number);
  BigUnsigned(const BigUnsigned& number) : digits_(number.digits_) {} // Constructor de copia

  BigUnsigned& operator=(const BigUnsigned& number); 
  friend std::ostream& operator<<(std::ostream& os, const BigUnsigned& number);
  friend std::istream& operator>>(std::istream&, BigUnsigned&); 
  bool operator==(const BigUnsigned& number) const;
  friend bool operator<(const BigUnsigned& number1, const BigUnsigned& number2);
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento
  friend BigUnsigned operator+(const BigUnsigned& number1, const BigUnsigned& number2);
  BigUnsigned operator-(const BigUnsigned& number) const;
  BigUnsigned operator*(const BigUnsigned& number) const;
  friend BigUnsigned operator/(const BigUnsigned& number1, const BigUnsigned& number2);
  BigUnsigned operator%(const BigUnsigned& number) const;

 private:
  std::vector<int> digits_;
};
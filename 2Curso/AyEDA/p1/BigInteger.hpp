#pragma once

#include "BigUnsigned.hpp"

class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&); // Constructor de cambio de tipo
 
  BigInteger& operator=(const BigInteger& number); 
  friend std::ostream& operator<<(std::ostream& os, const BigInteger& number);
  friend std::istream& operator>>(std::istream&, BigInteger&); 
  bool operator==(const BigInteger& number) const;
  friend bool operator<(const BigInteger& number1, const BigInteger& number2);
  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento
  friend BigInteger operator+(const BigInteger& number1, const BigInteger& number2);
  BigInteger operator-(const BigInteger& number) const;
  BigInteger operator*(const BigInteger& number) const;
  friend BigInteger operator/(const BigInteger& number1, const BigInteger& number2);
  BigInteger operator%(const BigInteger& number) const;

 private:
  BigUnsigned digits_;
  bool is_negative_;
};
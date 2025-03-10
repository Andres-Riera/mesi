#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

#include "Exceptions.hpp"

template<unsigned char Base>
class BigNumber;

template<unsigned char Base>
class BigRational;

template<unsigned char Base>
class BigInteger;

template<unsigned char Base>
class BigUnsigned;

template <unsigned char Base>
class BigNumber {
 public:
  virtual ~BigNumber() = default;

  virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;

  virtual operator BigUnsigned<Base>() const = 0;
  virtual operator BigInteger<Base>() const = 0;
  virtual operator BigRational<Base>() const = 0;

  static BigNumber<Base>* create(const char* number);
 protected:
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& number) {
    return number.write(os);
  }
  friend std::istream& operator>>(std::istream& is, BigNumber<Base>& number) {
    return number.read(is);
  }
};

#include "BigUnsignedPlantilla.hpp"
#include "BigIntegerPlantilla.hpp"
#include "BigRationalPlantilla.hpp"

template<unsigned char Base>
BigNumber<Base>* BigNumber<Base>::create(const char* number)  {
  std::string str(number);
  if (str.back() == 'u') {
    return new BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(str.substr(0, str.size() - 1).c_str()));
  } else if (str.back() == 'i') {
    return new BigInteger<Base>(reinterpret_cast<const unsigned char*>(str.substr(0, str.size() - 1).c_str()));
  } else if (str.back() == 'r') {
    size_t pos = str.find('/');
    if (pos != std::string::npos) {
      std::string numerator = str.substr(0, pos);
      std::string denominator = str.substr(pos + 1, str.size() - pos - 2);
      return new BigRational<Base>(
        BigInteger<Base>(reinterpret_cast<const unsigned char*>(numerator.c_str())), 
        BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(denominator.c_str()))
      );
    }
  }
  throw std::invalid_argument("Invalid number format");
}
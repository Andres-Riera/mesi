#pragma once

#include "BigUnsignedPlantilla.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// Declaración anticipada de la plantilla de funciones friend
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& number);
template<unsigned char Base>
std::istream& operator>>(std::istream&, BigInteger<Base>&); 
template<unsigned char Base>
bool operator<(const BigInteger<Base>& number1, const BigInteger<Base>& number2);
template<unsigned char Base>
BigInteger<Base> operator+(const BigInteger<Base>& number1, const BigInteger<Base>& number2);
template<unsigned char Base>
BigInteger<Base> operator/(const BigInteger<Base>& number1, const BigInteger<Base>& number2);

template <unsigned char Base>
class BigInteger : public BigNumber<Base> {
 public:
  BigInteger(int n = 0);
  BigInteger(const unsigned char *number);
  BigInteger(const BigUnsigned<Base> &); // Constructor de cambio de tipo
  ~BigInteger() = default;

  BigInteger<Base> &operator=(const BigInteger<Base> &number);
  friend std::ostream &operator<< <>(std::ostream &os, const BigInteger<Base> &number);
  friend std::istream &operator>> <>(std::istream &, BigInteger<Base> &);
  bool operator==(const BigInteger<Base> &number) const;
  friend bool operator< <>(const BigInteger<Base> &number1, const BigInteger<Base> &number2);
  BigInteger<Base> &operator++();   // Pre-incremento
  BigInteger<Base> operator++(int); // Post-incremento
  BigInteger<Base> &operator--();   // Pre-decremento
  BigInteger<Base> operator--(int); // Post-decremento
  friend BigInteger<Base> operator+ <>(const BigInteger<Base> &number1, const BigInteger<Base> &number2);
  BigInteger<Base> operator-(const BigInteger<Base> &number) const;
  BigInteger<Base> operator*(const BigInteger<Base> &number) const;
  friend BigInteger<Base> operator/ <>(const BigInteger<Base> &number1, const BigInteger<Base> &number2);
  BigInteger<Base> operator%(const BigInteger<Base> &number) const;
  BigUnsigned<Base> GetUnsigned() const { return digits_; }

  virtual operator BigUnsigned<Base>() const override { return digits_; }
  virtual operator BigInteger<Base>() const override { return *this; }
  virtual operator BigRational<Base>() const override { 
    BigUnsigned<Base> den(1);
    return BigRational<Base>(*this, den); 
  }

  virtual BigNumber<Base>& add(const BigNumber<Base>& number) const override {
    const BigInteger<Base> other = number;
    auto* result = new BigInteger<Base>(*this + other);
    return *result;
  }

  virtual BigNumber<Base>& subtract(const BigNumber<Base>& number) const override {
    const BigInteger<Base> other = number;
    auto* result = new BigInteger<Base>(*this - other);
    return *result;
  }
  virtual BigNumber<Base>& multiply(const BigNumber<Base>& number) const override {
    const BigInteger<Base> other = number;
    auto* result = new BigInteger<Base>(*this * other);
    return *result;
  }
  virtual BigNumber<Base>& divide(const BigNumber<Base>& number) const override {
    const BigInteger<Base> other = number;
    auto* result = new BigInteger<Base>(*this / other);
    return *result;
  }

 protected:
  std::ostream& write(std::ostream& os) const override {
    return os << *this << 'i';
  }
  std::istream& read(std::istream& is) override {
    return is >> *this;
  }

 private:
  BigUnsigned<Base> digits_;
  bool is_negative_;
};

template<unsigned char Base>
BigInteger<Base>::BigInteger(int n) {
  if (n < 0) {
    is_negative_ = true;
    n *= -1;
    BigUnsigned<Base> tempBigUnsigned(static_cast<unsigned>(n));
    digits_ = tempBigUnsigned;
  } else {
    is_negative_ = false;
    BigUnsigned<Base> tempBigUnsigned(static_cast<unsigned>(n));
    digits_ = tempBigUnsigned;
  }
}

template<unsigned char Base>
BigInteger<Base>::BigInteger(const unsigned char* number) {
  std::string number_str(reinterpret_cast<const char*>(number));
  if (number_str[0] == '-') {
    is_negative_ = true;
    number_str = number_str.substr(1);
  } else {
    is_negative_ = false;
  }
  BigUnsigned<Base> tempBigUnsigned(reinterpret_cast<const unsigned char*>(number_str.c_str()));
  digits_ = tempBigUnsigned;
}

template<unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& number) {
  is_negative_ = false;
  digits_ = number;
} // Constructor de cambio de tipo

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& number) {
  this->digits_ = number.digits_;
  this->is_negative_ = number.is_negative_;
  return *this;
}

template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& number) {
  if (number.is_negative_ && !(number.digits_ == BigUnsigned<Base>(unsigned(0)))) {
    os << '-';
  }
  os << number.digits_;
  return os;
}

template<unsigned char Base>
std::istream& operator>>(std::istream& in, BigInteger<Base>& number) {
  int sign;
  in >> sign >> number.digits_;
  if (sign != 0 && sign != 1) {
    throw std::invalid_argument("Invalid sign.");
  }
  number.is_negative_ = sign;
  return in;
}

template<unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& number) const {
  return (this->digits_ == number.digits_ && this->is_negative_ == number.is_negative_);
}

template<unsigned char Base>
bool operator<(const BigInteger<Base>& number1, const BigInteger<Base>& number2) {
  if (number1.is_negative_ && number2.is_negative_) {
      return !(number2.digits_ < number1.digits_);
  }
  else if (number1.is_negative_ && !number2.is_negative_) {
      return true;
  }
  else if (!number1.is_negative_ && number2.is_negative_) {
      return false;
  }
  else {
      return number1.digits_ < number2.digits_;
  }
}

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator++() {
  BigInteger<Base> one(1);
  *this = *this + one;
  return *this;
} // Pre-incremento

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator++(int) {
  BigInteger<Base> temp = *this; 
    *this = *this + BigInteger<Base>(1);
    return temp;
}; // Post-incremento

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator--() {
  BigInteger<Base> one(1);
  *this = *this - one;
  return *this;
}; // Pre-decremento

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator--(int) {
  BigInteger<Base> temp = *this;
  *this = *this - BigInteger<Base>(1);
  return temp;
}; // Post-decremento

template<unsigned char Base>
BigInteger<Base> operator+(const BigInteger<Base>& number1, const BigInteger<Base>& number2) {
  BigInteger<Base> result;
  if (number1.is_negative_ && number2.is_negative_) {
      result.digits_ = number1.digits_ + number2.digits_;
      result.is_negative_ = true;
  } else if (number1.is_negative_ && !number2.is_negative_) {
      if (number1.digits_ < number2.digits_) {
          result.digits_ = number2.digits_ - number1.digits_;
          result.is_negative_ = false;
      } else {
          result.digits_ = number1.digits_ - number2.digits_;
          result.is_negative_ = true;
      }
  } else if (!number1.is_negative_ && number2.is_negative_) {
      if (number1.digits_ < number2.digits_) {
          result.digits_ = number2.digits_ - number1.digits_;
          result.is_negative_ = true;
      } else {
          result.digits_ = number1.digits_ - number2.digits_;
          result.is_negative_ = false;
      }
  } else {
      result.digits_ = number1.digits_ + number2.digits_;
      result.is_negative_ = false;
  }
  BigInteger<Base> zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& number) const {
  BigInteger<Base> result;
  if (this->is_negative_ && number.is_negative_) {
      if (this->digits_ < number.digits_) {
          result.digits_ = number.digits_ - this->digits_;
          result.is_negative_ = true;
      } else {
          result.digits_ = this->digits_ - number.digits_;
          result.is_negative_ = false;
      }
  } 
  else if (this->is_negative_ && !number.is_negative_) {
      result.digits_ = this->digits_ + number.digits_;
      result.is_negative_ = true;
  } 
  else if (!this->is_negative_ && number.is_negative_) {
      result.digits_ = this->digits_ + number.digits_;
      result.is_negative_ = false;
  } 
  else {
      if (this->digits_ < number.digits_) {
          result.digits_ = number.digits_ - this->digits_;
          result.is_negative_ = true;
      } else {
          result.digits_ = this->digits_ - number.digits_;
          result.is_negative_ = false;
      }
  }
  BigInteger<Base> zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& number) const {
  BigInteger<Base> result;
  result.digits_ = this->digits_ * number.digits_;
  result.is_negative_ = (this->is_negative_ != number.is_negative_);
  BigInteger<Base> zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

template<unsigned char Base>
BigInteger<Base> operator/(const BigInteger<Base>& number1, const BigInteger<Base>& number2) {
  if (number2 == BigInteger<Base>(0)) {
    throw BigNumberDivisionByZero();
  }
  BigInteger<Base> result;
  result.digits_ = number1.digits_ / number2.digits_;
  result.is_negative_ = (number1.is_negative_ != number2.is_negative_);
  BigInteger<Base> zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& number) const {
  if (number == BigInteger<Base>(0)) {
    throw BigNumberDivisionByZero();
  }
  BigInteger<Base> result;
  result.digits_ = this->digits_ % number.digits_;
  result.is_negative_ = this->is_negative_;
  BigInteger<Base> zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}
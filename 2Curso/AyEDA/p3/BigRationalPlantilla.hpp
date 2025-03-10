#pragma once

#include "BigIntegerPlantilla.hpp"
#include "BigUnsignedPlantilla.hpp"
#include <iostream>
#include <stdexcept>

// Declaración anticipada de la plantilla de funciones friend
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& number);
template<unsigned char Base>
std::istream& operator>>(std::istream&, BigRational<Base>&); 
template<unsigned char Base>
bool operator<(const BigRational<Base>& number1, const BigRational<Base>& number2);
template<unsigned char Base>
BigRational<Base> operator+(const BigRational<Base>& number1, const BigRational<Base>& number2);
template<unsigned char Base>
BigRational<Base> operator/(const BigRational<Base>& number1, const BigRational<Base>& number2);

template <unsigned char Base>
class BigRational : public BigNumber<Base> {
 public:
  BigRational(const BigInteger<Base> &numerator = 0, const BigUnsigned<Base> &denominator = 1) 
    : numerator_(numerator), denominator_(denominator) {
    BigUnsigned<Base> zero(static_cast<unsigned int>(0));
    if (denominator == zero) {
      throw BigNumberDivisionByZero();
    }
    Simplify_();
  }
  BigRational(const BigRational<Base>& number) : numerator_(number.numerator_), denominator_(number.denominator_) {}
  ~BigRational() = default;

  BigRational<Base>& operator=(const BigRational<Base> &number) {
    if (this != &number) {
      numerator_ = number.numerator_;
      denominator_ = number.denominator_;
    }
    return *this;
  }
  friend std::ostream& operator<< <>(std::ostream &os, const BigRational<Base> &number);
  friend std::istream& operator>> <>(std::istream &, BigRational<Base> &);
  bool operator==(const BigRational<Base> &number) const {
    return numerator_ == number.numerator_ && denominator_ == number.denominator_;
  }
  friend bool operator< <>(const BigRational<Base> &number1, const BigRational<Base> &number2);
  friend BigRational<Base> operator+ <>(const BigRational<Base> &number1, const BigRational<Base> &number2);
  BigRational<Base> operator-(const BigRational<Base> &number) const {
    BigRational<Base> result;
    BigInteger<Base> den1(denominator_);
    BigInteger<Base> den2(number.denominator_);
    result.numerator_ = numerator_ * den2 - number.numerator_ * den1;
    result.denominator_ = denominator_ * number.denominator_;
    result.Simplify_();
    return result;
  }
  BigRational<Base> operator*(const BigRational<Base> &number) const {
    BigRational<Base> result;
    result.numerator_ = numerator_ * number.numerator_;
    result.denominator_ = denominator_ * number.denominator_;
    result.Simplify_();
    return result;
  }
  friend BigRational<Base> operator/ <>(const BigRational<Base> &number1, const BigRational<Base> &number2);

  virtual operator BigUnsigned<Base>() const override { return numerator_.GetUnsigned() / denominator_; }
  virtual operator BigInteger<Base>() const override { 
    BigInteger<Base> den(denominator_);
    return numerator_ / den; 
  }
  virtual operator BigRational<Base>() const override { return *this; }

  virtual BigNumber<Base>& add(const BigNumber<Base>& number) const override {
    const BigRational<Base> other = number;
    auto* result = new BigRational<Base>(*this + other);
    return *result;
  }

  virtual BigNumber<Base>& subtract(const BigNumber<Base>& number) const override {
    const BigRational<Base> other = number;
    auto* result = new BigRational<Base>(*this - other);
    return *result;
  }
  virtual BigNumber<Base>& multiply(const BigNumber<Base>& number) const override {
    const BigRational<Base> other = number;
    auto* result = new BigRational<Base>(*this * other);
    return *result;
  }
  virtual BigNumber<Base>& divide(const BigNumber<Base>& number) const override {
    const BigRational<Base> other = number;
    auto* result = new BigRational<Base>(*this / other);
    return *result;
  }

 protected:
  std::ostream& write(std::ostream& os) const override {
    return os << *this << 'r';
  }
  std::istream& read(std::istream& is) override {
    return is >> *this;
  }

 private:
  BigUnsigned<Base> denominator_;
  BigInteger<Base> numerator_;
  void Simplify_() {
    BigUnsigned<Base> numerator = numerator_.GetUnsigned();
    BigUnsigned<Base> denominator = denominator_;
    BigUnsigned<Base> mcd = mcd_(numerator, denominator);
    BigInteger<Base> aux(mcd);
    numerator_ = numerator_ / aux;
    denominator_ = denominator / mcd;
  }
  BigUnsigned<Base> mcd_(BigUnsigned<Base> num1, BigUnsigned<Base> num2) {
    BigUnsigned<Base> zero(static_cast<unsigned int>(0));
    if (num2 == zero) {
      return num1;
    } else {
      return mcd_(num2, num1 % num2);
    }
  }
};

template<unsigned char Base>
std::ostream &operator<<(std::ostream &os, const BigRational<Base> &number) {
  BigRational<Base> simplified_number = number;
  simplified_number.Simplify_();
  os << simplified_number.numerator_ << '/' << simplified_number.denominator_;
  return os;
}

template<unsigned char Base>
std::istream &operator>>(std::istream &in, BigRational<Base> &number) {
  in >> number.numerator_ >> number.denominator_;
  if (number.denominator_ == BigUnsigned<Base>(static_cast<unsigned int>(0))) {
    throw std::runtime_error("Division by zero");
  }
  number.Simplify_();
  return in;
}

template<unsigned char Base>
bool operator<(const BigRational<Base> &number1, const BigRational<Base> &number2) {
  BigUnsigned<Base> num1 = number1.numerator_.GetUnsigned() * number2.denominator_;
  BigUnsigned<Base> num2 = number2.numerator_.GetUnsigned() * number1.denominator_;
  return num1 < num2;
}

template<unsigned char Base>
BigRational<Base> operator+(const BigRational<Base> &number1, const BigRational<Base> &number2) {
  BigRational<Base> result;
  BigInteger<Base> den1(number1.denominator_);
  BigInteger<Base> den2(number2.denominator_);
  result.numerator_ = number1.numerator_ * den2 + number2.numerator_ * den1;
  result.denominator_ = number1.denominator_ * number2.denominator_;
  result.Simplify_();
  return result;
}

template<unsigned char Base>
BigRational<Base> operator/(const BigRational<Base> &number1, const BigRational<Base> &number2) {
  BigInteger<Base> zero(static_cast<int>(0));
  if (number2.numerator_ == zero) {
    throw BigNumberDivisionByZero();
  }
  BigRational<Base> result;
  BigInteger<Base> den2(number2.denominator_);
  result.numerator_ = number1.numerator_ * den2;
  result.denominator_ = number1.denominator_ * number2.numerator_.GetUnsigned();
  result.Simplify_();
  return result;
}
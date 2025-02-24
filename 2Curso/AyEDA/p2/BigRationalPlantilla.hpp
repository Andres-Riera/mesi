#pragma once

#include "BigIntegerPlantilla.hpp"

template<unsigned char Base>
class BigRational; // Declaración anticipada de la clase

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
class BigRational {
 public:
  BigRational(const BigInteger<Base> &numerator = 0, const BigUnsigned<Base> &denominator = 1);
  BigRational(const BigRational<Base>& number) : numerator_(number.numerator_), denominator_(number.denominator_) {}

  BigRational<Base> &operator=(const BigRational<Base> &number);
  friend std::ostream &operator<< <>(std::ostream &os, const BigRational<Base> &number);
  friend std::istream &operator>> <>(std::istream &, BigRational<Base> &);
  bool operator==(const BigRational<Base> &number) const;
  friend bool operator< <>(const BigRational<Base> &number1, const BigRational<Base> &number2);
  friend BigRational<Base> operator+ <>(const BigRational<Base> &number1, const BigRational<Base> &number2);
  BigRational<Base> operator-(const BigRational<Base> &number) const;
  BigRational<Base> operator*(const BigRational<Base> &number) const;
  friend BigRational<Base> operator/ <>(const BigRational<Base> &number1, const BigRational<Base> &number2);

 private:
  BigUnsigned<Base> denominator_;
  BigInteger<Base> numerator_;
  void Simplify_();
  BigUnsigned<Base> mcd_(BigUnsigned<Base> num1, BigUnsigned<Base> num2);
};

template<unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base> &numerator, const BigUnsigned<Base> &denominator)
  : numerator_(numerator), denominator_(denominator) {
  BigUnsigned<Base> zero(static_cast<unsigned int>(0));
  if (denominator == zero) {
    throw std::runtime_error("Division by zero");
  }
  Simplify_();
}

template<unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base> &number) {
  if (this != &number) {
    numerator_ = number.numerator_;
    denominator_ = number.denominator_;
  }
  return *this;
}

template<unsigned char Base>
BigUnsigned<Base> BigRational<Base>::mcd_(BigUnsigned<Base> num1, BigUnsigned<Base> num2) {
  BigUnsigned<Base> zero(static_cast<unsigned int>(0));
  if (num2 == zero) {
    return num1;
  } else {
    return mcd_(num2, num1 % num2);
  }
}

template<unsigned char Base>
void BigRational<Base>::Simplify_() {
  BigUnsigned<Base> numerator = numerator_.GetUnsigned();
  BigUnsigned<Base> denominator = denominator_;
  BigUnsigned<Base> mcd = mcd_(numerator, denominator);
  numerator_ = numerator / mcd;
  denominator_ = denominator / mcd;
}

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
  if (number.denominator_ == BigUnsigned<Base>(0)) {
    throw std::runtime_error("Division by zero");
  }
  number.Simplify_();
  return in;
}

template<unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base> &number) const {
  return numerator_ == number.numerator_ && denominator_ == number.denominator_;
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
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base> &number) const {
  BigRational<Base> result;
  BigInteger<Base> den1(denominator_);
  BigInteger<Base> den2(number.denominator_);
  result.numerator_ = numerator_ * den2 - number.numerator_ * den1;
  result.denominator_ = denominator_ * number.denominator_;
  result.Simplify_();
  return result;
}

template<unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base> &number) const {
  BigRational<Base> result;
  result.numerator_ = numerator_ * number.numerator_;
  result.denominator_ = denominator_ * number.denominator_;
  result.Simplify_();
  return result;
}

template<unsigned char Base>
BigRational<Base> operator/(const BigRational<Base> &number1, const BigRational<Base> &number2) {
  BigInteger<Base> zero(static_cast<int>(0));
  if (number2.numerator_ == zero) {
    throw std::runtime_error("Division by zero");
  }
  BigRational<Base> result;
  BigInteger<Base> den2(number2.denominator_);
  result.numerator_ = number1.numerator_ * den2;
  result.denominator_ = number1.denominator_ * number2.numerator_.GetUnsigned();
  result.Simplify_();
  return result;
}
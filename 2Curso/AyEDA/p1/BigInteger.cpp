#include "BigInteger.hpp"

BigInteger::BigInteger(int n) {
  if (n < 0) {
    is_negative_ = true;
    n *= -1;
    BigUnsigned tempBigUnsigned(static_cast<unsigned>(n));
    digits_ = tempBigUnsigned;

  } else {
    is_negative_ = false;
    BigUnsigned tempBigUnsigned(static_cast<unsigned>(n));
    digits_ = tempBigUnsigned;
  }
}

BigInteger::BigInteger(const BigUnsigned& number) {
  is_negative_ = false;
  digits_ = number;
} // Constructor de cambio de tipo

BigInteger& BigInteger::operator=(const BigInteger& number) {
  this->digits_ = number.digits_;
  this->is_negative_ = number.is_negative_;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
  if (number.is_negative_ && !(number.digits_ == BigUnsigned(unsigned(0)))) {
    os << '-';
  }
  os << number.digits_;
  return os;
}

std::istream& operator>>(std::istream& in, BigInteger& number) {
  int sign;
  in >> sign >> number.digits_;
  if (sign != 0 && sign != 1) {
    throw std::invalid_argument("Invalid sign.");
  }
  number.is_negative_ = sign;
  return in;
}

bool BigInteger::operator==(const BigInteger& number) const {
  return (this->digits_ == number.digits_ && this->is_negative_ == number.is_negative_);
}

bool operator<(const BigInteger& number1, const BigInteger& number2) {
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


BigInteger& BigInteger::operator++() {
  BigInteger one(1);
  *this = *this + one;
  return *this;
} // Pre-incremento

BigInteger BigInteger::operator++(int) {
  BigInteger temp = *this; 
    *this = *this + BigInteger(1);
    return temp;
}; // Post-incremento

BigInteger& BigInteger::operator--() {
  BigInteger one(1);
  *this = *this - one;
  return *this;
}; // Pre-decremento

BigInteger BigInteger::operator--(int) {
  BigInteger temp = *this;
  *this = *this - BigInteger(1);
  return temp;
}; // Post-decremento

BigInteger operator+(const BigInteger& number1, const BigInteger& number2) {
  BigInteger result;
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
  BigInteger zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

BigInteger BigInteger::operator-(const BigInteger& number) const {
  BigInteger result;
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
  BigInteger zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}


BigInteger BigInteger::operator*(const BigInteger& number) const {
  BigInteger result;
  result.digits_ = this->digits_ * number.digits_;
  result.is_negative_ = (this->is_negative_ != number.is_negative_);
  BigInteger zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}


BigInteger operator/(const BigInteger& number1, const BigInteger& number2) {
  if (number2 == BigInteger(0)) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  BigInteger result;
  result.digits_ = number1.digits_ / number2.digits_;
  result.is_negative_ = (number1.is_negative_ != number2.is_negative_);
  BigInteger zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

BigInteger BigInteger::operator%(const BigInteger& number) const {
  if (number == BigInteger(0)) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  BigInteger result;
  result.digits_ = this->digits_ % number.digits_;
  result.is_negative_ = this->is_negative_;
  BigInteger zero {0};
  if (result.digits_ == zero.digits_) {
    result.is_negative_ = false;
  }
  return result;
}

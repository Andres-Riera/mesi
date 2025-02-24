#pragma once

#include "BigUnsignedPlantila.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template<unsigned char Base>
class BigInteger; // Declaración anticipada de la clase

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
class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const unsigned char *number);
  BigInteger(const BigUnsigned<Base> &); // Constructor de cambio de tipo

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
    throw std::invalid_argument("Division by zero.");
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
    throw std::invalid_argument("Division by zero.");
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

// Especialización para la base 2
template<>
class BigInteger<2> {
 public:
  BigInteger(int n = 0);
  BigInteger(const unsigned char* number);

  BigInteger<2>& operator=(const BigInteger<2> &number);
  friend std::ostream& operator<<(std::ostream &os, const BigInteger<2> &number);
  friend std::istream& operator>>(std::istream &, BigInteger<2> &);
  bool operator==(const BigInteger<2> &number) const;
  friend bool operator<(const BigInteger<2> &number1, const BigInteger<2> &number2);
  BigInteger<2>& operator++();   // Pre-incremento
  BigInteger<2> operator++(int); // Post-incremento
  BigInteger<2>& operator--();   // Pre-decremento
  BigInteger<2> operator--(int); // Post-decremento
  friend BigInteger<2> operator+(const BigInteger<2> &number1, const BigInteger<2> &number2);
  BigInteger<2> operator-(const BigInteger<2> &number) const;
  BigInteger<2> operator*(const BigInteger<2> &number) const;
  friend BigInteger<2> operator/(const BigInteger<2> &number1, const BigInteger<2> &number2);
  BigInteger<2> operator%(const BigInteger<2> &number) const;
  BigUnsigned<2> GetUnsigned() const;

 private:
  std::vector<bool> digits_;
  bool is_negative_;
};

BigInteger<2>::BigInteger(int n) {
  if (n < 0) {
    is_negative_ = true;
    n = -n;
  } else {
    is_negative_ = false;
  }
  while (n > 0) {
    digits_.push_back(n % 2);
    n /= 2;
  }
  if (digits_.empty()) {
    digits_.push_back(0);
  }
}

BigInteger<2>::BigInteger(const unsigned char *number) {
  std::string number_str(reinterpret_cast<const char*>(number));
  if (number_str[0] == '-') {
    is_negative_ = true;
    number_str = number_str.substr(1);
  } else {
    is_negative_ = false;
  }
  for (char c : number_str) {
    if (c == '0') {
      digits_.push_back(false);
    } else if (c == '1') {
      digits_.push_back(true);
    } else {
      throw std::invalid_argument("Invalid number.");
    }
  }
  std::reverse(digits_.begin(), digits_.end());
}


BigInteger<2> &BigInteger<2>::operator=(const BigInteger<2> &number) {
  digits_ = number.digits_;
  is_negative_ = number.is_negative_;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const BigInteger<2> &number) {
  if (number.is_negative_) {
    os << '-';
  }
  for (auto it = number.digits_.rbegin(); it != number.digits_.rend(); ++it) {
    os << (*it ? '1' : '0');
  }
  return os;
}

std::istream &operator>>(std::istream &in, BigInteger<2> &number) {
  std::string input;
  in >> input;
  number.digits_.clear();
  if (input[0] == '-') {
    number.is_negative_ = true;
    input = input.substr(1);
  } else {
    number.is_negative_ = false;
  }
  for (char c : input) {
    if (c == '0') {
      number.digits_.push_back(false);
    } else if (c == '1') {
      number.digits_.push_back(true);
    } else {
      throw std::invalid_argument("Invalid character in binary number");
    }
  }
  std::reverse(number.digits_.begin(), number.digits_.end());
  return in;
}

bool BigInteger<2>::operator==(const BigInteger<2> &number) const {
  return digits_ == number.digits_ && is_negative_ == number.is_negative_;
}

bool operator<(const BigInteger<2> &number1, const BigInteger<2> &number2) {
  if (number1.is_negative_ && !number2.is_negative_) {
    return true;
  }
  if (!number1.is_negative_ && number2.is_negative_) {
    return false;
  }
  if (number1.digits_.size() != number2.digits_.size()) {
    return number1.digits_.size() < number2.digits_.size();
  }
  for (size_t i = number1.digits_.size(); i-- > 0;) {
    if (number1.digits_[i] != number2.digits_[i]) {
      return number1.digits_[i] < number2.digits_[i];
    }
  }
  return false;
}

BigInteger<2> &BigInteger<2>::operator++() {
  bool carry = true;
  for (auto &bit : digits_) {
    bool new_bit = bit ^ carry;
    carry = bit & carry;
    bit = new_bit;
    if (!carry) {
      break;
    }
  }
  if (carry) {
    digits_.push_back(true);
  }
  return *this;
}

BigInteger<2> BigInteger<2>::operator++(int) {
  BigInteger<2> temp = *this;
  ++(*this);
  return temp;
}

BigInteger<2> &BigInteger<2>::operator--() {
  bool carry = true;
  for (bool bit : digits_) {
    bool new_bit = bit ^ carry;
    carry = !bit & carry;
    bit = new_bit;
    if (!carry) {
      break;
    }
  }
  if (digits_.back() == false) {
    digits_.pop_back();
  }
  return *this;
}

BigInteger<2> BigInteger<2>::operator--(int) {
  BigInteger<2> temp = *this;
  --(*this);
  return temp;
}

BigInteger<2> operator+(const BigInteger<2> &number1, const BigInteger<2> &number2) {
  BigInteger<2> result;
  result.digits_.resize(std::max(number1.digits_.size(), number2.digits_.size()));
  bool carry = false;
  for (size_t i = 0; i < result.digits_.size(); ++i) {
    bool bit1 = i < number1.digits_.size() ? number1.digits_[i] : false;
    bool bit2 = i < number2.digits_.size() ? number2.digits_[i] : false;
    result.digits_[i] = bit1 ^ bit2 ^ carry;
    carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);
  }
  if (carry) {
    result.digits_.push_back(true);
  }
  return result;
}

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2> &number) const {
  BigInteger<2> complement = number;
  for (auto &bit : complement.digits_) {
    bit = !bit;
  }
  ++complement;
  return *this + complement;
}

BigInteger<2> BigInteger<2>::operator*(const BigInteger<2> &number) const {
  BigInteger<2> result;
  result.digits_.resize(digits_.size() + number.digits_.size());
  for (size_t i = 0; i < digits_.size(); ++i) {
    if (digits_[i]) {
      for (size_t j = 0; j < number.digits_.size(); ++j) {
        result.digits_[i + j] ^= number.digits_[j];
      }
    }
  }
  return result;
}

BigInteger<2> operator/(const BigInteger<2> &number1, const BigInteger<2> &number2) {
  if (number2 == BigInteger<2>(0)) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  BigInteger<2> result;
  BigInteger<2> remainder = number1;
  BigInteger<2> divisor = number2;
  while (remainder >= divisor) {
    BigInteger<2> temp = divisor;
    size_t shift = remainder.digits_.size() - divisor.digits_.size();
    temp.digits_.insert(temp.digits_.begin(), shift, false);
    if (remainder < temp) {
      temp.digits_.erase(temp.digits_.begin());
      --shift;
    }
    remainder = remainder - temp;
    result.digits_.insert(result.digits_.begin(), shift, false);
    result.digits_[shift] = true;
  }
  return result;
}

BigInteger<2> BigInteger<2>::operator%(const BigInteger<2> &number) const {
  if (number == BigInteger<2>(0)) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }
  BigInteger<2> remainder = *this;
  BigInteger<2> divisor = number;
  while (remainder >= divisor) {
    BigInteger<2> temp = divisor;
    size_t shift = remainder.digits_.size() - divisor.digits_.size();
    temp.digits_.insert(temp.digits_.begin(), shift, false);
    if (remainder < temp) {
      temp.digits_.erase(temp.digits_.begin());
      --shift;
    }
    remainder = remainder - temp;
  }
  return remainder;
}

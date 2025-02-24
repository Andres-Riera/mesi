#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

template<unsigned char Base>
class BigUnsigned; // Declaración anticipada de la clase

// Declaración anticipada de la plantilla de funciones friend
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& number);
template<unsigned char Base>
std::istream& operator>>(std::istream&, BigUnsigned<Base>&); 
template<unsigned char Base>
bool operator<(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);
template<unsigned char Base>
BigUnsigned<Base> operator+(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);
template<unsigned char Base>
BigUnsigned<Base> operator/(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);


template<unsigned char Base>
class BigUnsigned {
 public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* number);
  BigUnsigned(const BigUnsigned<Base>& number) : digits_(number.digits_) {} // Constructor de copia

  BigUnsigned<Base>& operator=(const BigUnsigned<Base>& number);
  friend std::ostream& operator<< <>(std::ostream& os, const BigUnsigned<Base>& number);
  friend std::istream& operator>> <>(std::istream&, BigUnsigned<Base>&); 
  bool operator==(const BigUnsigned<Base>& number) const;
  friend bool operator< <>(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);
  BigUnsigned<Base>& operator++(); // Pre-incremento
  BigUnsigned<Base> operator++(int); // Post-incremento
  BigUnsigned<Base>& operator--(); // Pre-decremento
  BigUnsigned<Base> operator--(int); // Post-decremento
  friend BigUnsigned<Base> operator+ <>(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);
  BigUnsigned<Base> operator-(const BigUnsigned<Base>& number) const;
  BigUnsigned<Base> operator*(const BigUnsigned<Base>& number) const;
  friend BigUnsigned<Base> operator/ <>(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2);
  BigUnsigned<Base> operator%(const BigUnsigned<Base>& number) const;

 private:
  std::vector<int> digits_;
};

template<unsigned char Base>
BigUnsigned<Base>::BigUnsigned(unsigned n) {
  if (n == 0) {
    digits_.push_back(0);
    return;
  }

  while (n > 0) {
    digits_.push_back(n % Base);
    n /= Base;
  }
}

template<unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* number) {
  std::string number_str(reinterpret_cast<const char*>(number));
  digits_.clear();
  for (char c : number_str) {
    int digit_value;
    if (c >= '0' && c <= '9') {
      digit_value = c - '0';
    } else if (c >= 'A' && c <= 'Z') {
      digit_value = 10 + (c - 'A');
    } else {
      throw std::invalid_argument("Invalid number.");
    }
    if (digit_value >= Base) {
      throw std::invalid_argument("Invalid number.");
    }
    digits_.push_back(digit_value);
  }
  std::reverse(digits_.begin(), digits_.end());
}

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& number) {
  if (this != &number) {
    digits_ = number.digits_;
  }
  return *this;
}

template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& number) {
  if (number.digits_.empty()) {
    os << "0";
    return os;
  }

  for (int i = number.digits_.size() - 1; i >= 0; --i) {
    if (number.digits_[i] < 10) {
      os << number.digits_[i];
    } else if (number.digits_[i] >= 10 && number.digits_[i] < 26) {
      os << static_cast<char>('A' + (number.digits_[i] - 10));
    }
  }
  return os;
}

template<unsigned char Base>
std::istream& operator>>(std::istream& in, BigUnsigned<Base>& number) {
  std::string input;
  in >> input;
  number.digits_.clear();
  bool zeros = true;
  for (char ch : input) {
    int digit_value;
    if (ch >= '0' && ch <= '9') {
      digit_value = ch - '0';
    } else if (ch >= 'A' && ch <= 'F') {
      digit_value = 10 + (ch - 'A');
    } else if (ch >= 'a' && ch <= 'f') {
      digit_value = 10 + (ch - 'a');
    } else {
      throw std::runtime_error("Invalid number.");
    }
    if (digit_value >= Base) {
      throw std::runtime_error("Invalid number.");
    }
    if (digit_value == 0 && zeros) {
      continue;
    } else {
      zeros = false;
    }
    number.digits_.push_back(digit_value);
  }
  if (number.digits_.empty()) {
    number.digits_.push_back(0);
  }
  std::reverse(number.digits_.begin(), number.digits_.end());
  return in;
}

template<unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& number) const {
  auto size1 {this->digits_.size()};
  auto size2 {number.digits_.size()};
  if (size1 != size2) {
    return false;
  }
  for (int i = 0; i < size1; i++) {
    if (this->digits_[i] != number.digits_[i]) {
      return false;        
    }
  }
  return true;
}

template<unsigned char Base>
bool operator<(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2) {
  auto size1 {number1.digits_.size()};
  auto size2 {number2.digits_.size()};
  if (size1 == size2) {
    for (int i = size1 - 1; i >= 0; i--) {
      if (number1.digits_[i] != number2.digits_[i]) {
        return number1.digits_[i] < number2.digits_[i];
      }
    }
  } else {
    return size1 < size2;
  }
  return false;
}

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator++() {
  BigUnsigned<Base> sum {1};
  *this = *this + sum;
  return *this;
} // Pre-incremento

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator++(int) {
  BigUnsigned<Base> temp = *this;
  ++(*this);
  return temp;
} // Post-incremento

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator--() {
  BigUnsigned<Base> sub {1};
  *this = *this - sub;
  return *this;
} // Pre-decremento

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator--(int) {
  BigUnsigned<Base> temp = *this;
  --(*this);
  return temp;
} // Post-decremento

template<unsigned char Base>
BigUnsigned<Base> operator+(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2) {
  auto size1 = number1.digits_.size();
  auto size2 = number2.digits_.size();
  int carry = 0;
  int i = 0;
  BigUnsigned<Base> result;
  result.digits_.resize(std::max(size1, size2));
  for (i; i < std::min(size1, size2); i++) {
      int sum = number1.digits_[i] + number2.digits_[i] + carry;
      result.digits_[i] = sum % Base;
      carry = sum / Base;
  }
  for (i; i < size1; i++) {
      int sum = number1.digits_[i] + carry;
      result.digits_[i] = sum % Base;
      carry = sum / Base;
  }
  for (i; i < size2; i++) {
      int sum = number2.digits_[i] + carry;
      result.digits_[i] = sum % Base;
      carry = sum / Base;
  }
  if (carry > 0) {
      result.digits_.push_back(carry);
  }
  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& number) const {
  if (*this < number) {
    unsigned zero {0};
    return BigUnsigned<Base>{zero};
  }
  BigUnsigned<Base> result = *this;
  auto size = result.digits_.size();
  for (int i = 0; i < size; i++) {
    int sub = result.digits_[i] - (i < number.digits_.size() ? number.digits_[i] : 0);
    if (sub < 0) {
      result.digits_[i] = sub + Base;
      int j = i + 1;
      while (j < result.digits_.size() && result.digits_[j] == 0) {
        result.digits_[j] = Base - 1;
        j++;
      }
      if (j < result.digits_.size()) {
        result.digits_[j] -= 1;
      }
    } else {
      result.digits_[i] = sub;
    }
  }
  while (result.digits_.size() > 1 && result.digits_.back() == 0) {
    result.digits_.pop_back();
  }
  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& number) const {
  BigUnsigned result;
  for (BigUnsigned<Base> zero(unsigned(0)); zero < number; zero++) {
    result = result + *this;
  }
  return result;
}

template<unsigned char Base>
BigUnsigned<Base> operator/(const BigUnsigned<Base>& number1, const BigUnsigned<Base>& number2) {
  unsigned zero {0};
  if (number2 == BigUnsigned<Base>(zero)) {
    throw std::runtime_error("Division by zero");
  }
  BigUnsigned<Base> copy {number1};
  BigUnsigned<Base> result {zero};
  while (!(copy < number2)) {
    copy = copy - number2;
    result++;
  }
  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& number) const {
  unsigned zero {0};
  if (number == BigUnsigned<Base>(zero)) {
    throw std::runtime_error("Division by zero");
  }
  BigUnsigned<Base> copy {*this};
  while (!(copy < number)) {
    copy = copy - number;
  }
  return copy;
}
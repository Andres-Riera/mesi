#include "BigUnsigned.hpp"

BigUnsigned::BigUnsigned(unsigned n) {
  if (n == 0) {
    digits_.push_back(0);
    return;
  }

  while (n > 0) {
    digits_.push_back(n % 10);
    n /= 10;
  }
}


BigUnsigned::BigUnsigned(const unsigned char* number) {
  std::string number_str(reinterpret_cast<const char*>(number));
  digits_.resize(number_str.size());
  for (int i = 0; i < number_str.size(); i++) {
    digits_[number_str.size() - 1 - i] = number_str[i] - '0';
  }
}


/*BigUnsigned::BigUnsigned(const BigUnsigned& number) {
  digits_.resize(number.digits_.size());
  for (int i = 0; i < number.digits_.size(); i++) {
    digits_[i] = number.digits_[i];
  }
} // Constructor de copia*/

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& number) {
  if (this != &number) {
    digits_ = number.digits_;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& number) {
  for (int i = number.digits_.size() - 1; i >= 0; i--) {
    unsigned char digit = static_cast<unsigned char>(number.digits_[i]) + '0';
    os << digit;
  }
  return os;
}

std::istream& operator>>(std::istream& in, BigUnsigned& number) {
  std::string input;
  in >> input;  
  number.digits_.resize(input.size());
  bool zeros = true;
  for (int i = 0; i < input.size(); i++) {
    if (input[i] < '0' || input[i] > '9') {
      throw std::runtime_error("Invalid number.");
    }
    if (input[i] == '0' && zeros) { 
      number.digits_.pop_back();
    } else {
      number.digits_[input.size() - 1 - i] = input[i] - '0';
      zeros = false;
    }
  }
  if (input == "0") {
    number.digits_.push_back(0);
  }
  return in;
}


bool BigUnsigned::operator==(const BigUnsigned& number) const {
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

bool operator<(const BigUnsigned& number1, const BigUnsigned& number2) {
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

BigUnsigned& BigUnsigned::operator++() {
  BigUnsigned sum {1};
  *this = *this + sum;
  return *this;
} // Pre-incremento

BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp = *this;
  ++(*this);
  return temp;
} // Post-incremento

BigUnsigned& BigUnsigned::operator--() {
  BigUnsigned sub {1};
  *this = *this - sub;
  return *this;
} // Pre-decremento

BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned temp = *this;
  --(*this);
  return temp;
} // Post-decremento

BigUnsigned operator+(const BigUnsigned& number1, const BigUnsigned& number2) {
  auto size1 = number1.digits_.size();
  auto size2 = number2.digits_.size();
  int carry = 0;
  int i = 0;
  BigUnsigned result;
  result.digits_.resize(std::max(size1, size2));
  for (i; i < std::min(size1, size2); i++) {
      int sum = number1.digits_[i] + number2.digits_[i] + carry;
      result.digits_[i] = sum % 10;
      carry = sum / 10;
  }
  for (i; i < size1; i++) {
      int sum = number1.digits_[i] + carry;
      result.digits_[i] = sum % 10;
      carry = sum / 10;
  }
  for (i; i < size2; i++) {
      int sum = number2.digits_[i] + carry;
      result.digits_[i] = sum % 10;
      carry = sum / 10;
  }
  if (carry > 0) {
      result.digits_.push_back(carry);
  }
  return result;
}


BigUnsigned BigUnsigned::operator-(const BigUnsigned& number) const {
  if (*this < number) {
    unsigned zero {0};
    return BigUnsigned{zero};
  }
  BigUnsigned result = *this;
  auto size = result.digits_.size();
  for (int i = 0; i < size; i++) {
    int sub = result.digits_[i] - (i < number.digits_.size() ? number.digits_[i] : 0);
    if (sub < 0) {
      result.digits_[i] = sub + 10;
      int j = i + 1;
      while (j < result.digits_.size() && result.digits_[j] == 0) {
        result.digits_[j] = 9;
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

/*BigUnsigned BigUnsigned::operator*(const BigUnsigned& number) const {
  BigUnsigned result;
  result.digits_.resize(this->digits_.size() + number.digits_.size(), 0);
  for (int i = 0; i < this->digits_.size(); i++) {
    for (int j = 0; j < number.digits_.size(); j++) {
      result.digits_[i + j] += this->digits_[i] * number.digits_[j];
      if (result.digits_[i + j] >= 10) {
        result.digits_[i + j + 1] += result.digits_[i + j] / 10;
        result.digits_[i + j] %= 10;
      }
    }
  }
  auto fsize = result.digits_.size() - 1;
  while(result.digits_[fsize] == 0 && fsize > 0) {
    result.digits_.pop_back();
    fsize--;
  }
  return result;
}
*/

BigUnsigned BigUnsigned::operator*(const BigUnsigned& number) const {
  BigUnsigned result;
  for (BigUnsigned zero(unsigned(0)); zero < number; zero++) {
    result = result + *this;
  }
  return result;
}

BigUnsigned operator/(const BigUnsigned& number1, const BigUnsigned& number2) {
  unsigned zero {0};
  if (number2 == BigUnsigned(zero)) {
    throw std::runtime_error("Division by zero");
  }
  BigUnsigned copy {number1};
  BigUnsigned result {zero};
  while (!(copy < number2)) {
    copy = copy - number2;
    result++;
  }
  return result;
}

BigUnsigned BigUnsigned::operator%(const BigUnsigned& number) const {
  unsigned zero {0};
  if (number == BigUnsigned(zero)) {
    throw std::runtime_error("Division by zero");
  }
  BigUnsigned copy {*this};
  while (!(copy < number)) {
    copy = copy - number;
  }
  return copy;
}
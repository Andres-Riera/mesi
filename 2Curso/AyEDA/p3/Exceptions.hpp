#pragma once

#include <exception>
#include <string>

class BigNumberException : public std::exception {
 public:
  explicit BigNumberException(const std::string& message) : message_(message) {}
  virtual const char* what() const noexcept override {
    return message_.c_str();
  }
 private:
  std::string message_;
};

class BigNumberBadDigit : public BigNumberException {
 public:
  BigNumberBadDigit(const std::string digit) : BigNumberException("\'" + digit + "\' is an invalid digit") {}
};

class BigNumberDivisionByZero : public BigNumberException {
 public:
  BigNumberDivisionByZero() : BigNumberException("Division by zero") {}
};
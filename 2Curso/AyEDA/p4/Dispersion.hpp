#pragma once

#include <cstdlib>  // Para std::rand
#include <ctime> // Para std::time

template <class Key>
class DispersionFunction {
public:
  virtual unsigned operator()(const Key& k) const = 0;
};

template <class Key>
class ModuloDispersion : public DispersionFunction<Key> {
 public:
  ModuloDispersion(unsigned size) : tableSize(size) {}
  unsigned operator()(const Key& k) const override {
    return k % tableSize;
  }
 private:
  unsigned tableSize;
};

template <class Key>
class SumDispersion : public DispersionFunction<Key> {
 public:
  SumDispersion(unsigned size) : tableSize(size) {}
  unsigned operator()(const Key& k) const override {
    unsigned sum = 0;
    int temp = static_cast<int>(k);
    while (temp > 0) {
      sum += temp % 10;
      temp /= 10;
    }
    return sum % tableSize;
  }
 private:
  unsigned tableSize;
};

template <class Key>
class PseudoRandomDispersion : public DispersionFunction<Key> {
 public:
  PseudoRandomDispersion(unsigned size) : tableSize(size) {
    std::srand(std::time(0));
  }
  unsigned operator()(const Key& k) const override {
    std::srand(k);
    return std::rand() % tableSize; 
  }

  private:
   unsigned tableSize;
};
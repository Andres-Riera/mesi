#pragma once

#include <cstdlib>  // Para std::rand

#include "Dispersion.hpp"

template <class Key>
class ExplorationFunction {
public:
    virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override {
    return i;
  }
};

template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override {
    return i * i;
  }
};

template <class Key>
class DoubleExploration : public ExplorationFunction<Key> {
 public:
  DoubleExploration(DispersionFunction<Key>& hash) : secondHash(hash) {}
  unsigned operator()(const Key& k, unsigned i) const override {
    return i * secondHash(k);
  }

 private:
  DispersionFunction<Key>& secondHash;
};

template <class Key>
class ReDispersionExploration : public ExplorationFunction<Key> {
 public:
  ReDispersionExploration(DispersionFunction<Key>& dispersion, unsigned size) : dispersionFunction(dispersion), tableSize(size) {}
  unsigned operator()(const Key& k, unsigned i) const override {
    return (dispersionFunction(k) + i) % tableSize;
  }

 private:
  DispersionFunction<Key>& dispersionFunction; 
  unsigned tableSize;
};
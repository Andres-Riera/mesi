#pragma once

#include <algorithm> // std::find
#include <list>
#include <iostream>
#include <vector>

template <class Key>
class Sequence {
 public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() const = 0; // Solo para dispersión cerrada
  virtual Key operator[](const unsigned) const = 0;
  virtual Key& operator[](const unsigned) = 0;
  virtual unsigned size() const = 0;
};

template <class Key>
class DynamicSequence : public Sequence<Key> {
 public:
  bool search(const Key& k) const override {
    return std::find(list.begin(), list.end(), k) != list.end();
  }
  bool insert(const Key& k) override {
    list.push_back(k);
    return true;
  }
  bool isFull() const override {
    return false; // Nunca está llena en dispersión abierta
  }
  Key operator[](const unsigned i) const override {
    auto it = std::next(list.begin(), i);
    return *it;
  }
  Key& operator[](const unsigned i) override {
    auto it = std::next(list.begin(), i);
    return *it;
  }

 private:
  std::list<Key> list;
};

template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(unsigned size) : blockSize(size) { block.resize(size); }
  bool search(const Key& k) const override {
    return std::find(block.begin(), block.end(), k) != block.end();
  }
  bool insert(const Key& k) override {
    if (isFull()) return false;
    block.push_back(k);
    return true;
    }
  bool isFull() const override {
    return block.size() >= blockSize;
  }
  
  Key operator[](const unsigned i) const override {
    return block[i];
  }
  Key& operator[](const unsigned i) override {
    return block[i];
  }

  unsigned size() const {
    return blockSize;
  }

 private:
  std::vector<Key> block;
  unsigned blockSize;
};

template <class Key>
void writeSequence(const Sequence<Key>& seq) {
  for (unsigned i = 0; i < seq.size(); ++i) {
    std::cout << seq[i] << " ";
  }
  std::cout << std::endl;
}
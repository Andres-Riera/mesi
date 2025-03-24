#pragma once

#include <algorithm> // std::find
#include <list>
#include <vector>

template <class Key>
class Sequence {
 public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() const = 0; // Solo para dispersión cerrada
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

 private:
  std::list<Key> list;
};

template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(unsigned size) : blockSize(size) {}
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

 private:
  std::vector<Key> block;
  unsigned blockSize;
};
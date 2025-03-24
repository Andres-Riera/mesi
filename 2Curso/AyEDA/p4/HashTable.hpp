#pragma once

#include <vector>

#include "Dispersion.hpp"
#include "Exploracion.hpp"
#include "Sequence.hpp"

template <class Key, class Container = StaticSequence<Key>>
class HashTable {
 public:
  HashTable(unsigned size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>* exploration = nullptr, unsigned bs = 1)
           : tableSize_(size), fd_(dispersion), fe_(exploration), blockSize_(bs) {
    table_.resize(tableSize_);
    for (unsigned i = 0; i < tableSize_; ++i) {
      if constexpr (std::is_same_v<Container, DynamicSequence<Key>>) {
        table_[i] = new Container();  // Sin argumentos para DynamicSequence
      } else {
        table_[i] = new Container(blockSize_);  // Con blockSize para StaticSequence
      }
    }
  }

  ~HashTable() {
    for (unsigned i = 0; i < tableSize_; ++i) {
      delete table_[i];
    }
  }

  bool insert(const Key& k, unsigned& position) {
    unsigned index = fd_(k);
    if (fe_) {
      unsigned i = 0;
      while (table_[index]->isFull()) {
        index = (fd_(k) + (*fe_)(k, i)) % tableSize_;
        i++;
        if (isFull_()) {
          position = tableSize_;
          return false;
        }
      }
    }
    bool success = table_[index]->insert(k);
    position = index;
    return success;
  }

  bool search(const Key& k, unsigned& position) const {
    unsigned index = fd_(k);
    if (fe_) {
      unsigned i = 0;
      while (i < tableSize_) {
        if (table_[index]->search(k)) {
          position = index;
          return true;
        }
        if (table_[index]->isFull()) {
          index = (fd_(k) + (*fe_)(k, i)) % tableSize_;
          i++;
        } else{
          return false;
        }
        return false;
      }
    }
    bool success = table_[index]->insert(k);
    position = index;
    return success;
  }

 private:
  unsigned tableSize_;
  std::vector<Container*> table_;
  DispersionFunction<Key>& fd_;
  ExplorationFunction<Key>* fe_;
  unsigned blockSize_;
  bool isFull_() {
    for (unsigned i = 0; i < tableSize_; ++i) {
      if (!table_[i]->isFull()) {
        return false;
      }
    }
    return true;
  }
};
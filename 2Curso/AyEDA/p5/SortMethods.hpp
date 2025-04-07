#pragma once 

#include "funciones.hpp"

template <class Key>
class SortMethod {
 public:
  SortMethod(StaticSequence<Key>* seq) : sequence(seq) {}
  virtual void Sort() = 0;

 protected:
  StaticSequence<Key>* sequence;
};

template <class Key>
class InsertionSort : public SortMethod<Key> {
 public:
  InsertionSort(StaticSequence<Key>* seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    Insercion(*this->sequence, this->sequence->size());
  }
};

template <class Key>
class ShakeSort : private SortMethod<Key> {
 public:
  ShakeSort(StaticSequence<Key>* seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    Sacudida(*this->sequence, this->sequence->size());
  }
};

template <class Key>
class QuickSort : private SortMethod<Key> {
 public:
  QuickSort(StaticSequence<Key>* seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    Quicksort(*this->sequence, 0, this->sequence->size() - 1);
  }
};

template <class Key>
class HeapSort : private SortMethod<Key> {
 public:
  HeapSort(StaticSequence<Key>* seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    Heapsort(*this->sequence, this->sequence->size());
  }
};

template <class Key>
class ShellSort : private SortMethod<Key> {
 public:
  ShellSort(StaticSequence<Key>* seq) : SortMethod<Key>(seq) {}
  void Sort() override {
    Shellsort(*this->sequence, this->sequence->size());
  }
};
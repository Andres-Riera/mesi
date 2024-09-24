// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// TEMA: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 

#pragma once 


#include <iostream>
#include <iomanip>
#include <cassert>

#include "matrix_t.hpp"

#define MAX_STACK_SIZE 200

using namespace std;

namespace AED
{
// Clase para pilas mediante estructura estática
template<class T> 
class stack_v_t {
 public:
  // constructores
  stack_v_t(int max_sz) : v_(max_sz), top_(-1) {}
  stack_v_t(void) : v_(MAX_STACK_SIZE), top_(-1) {}

  // destructor
  ~stack_v_t(void) {}

  // operaciones
  void push(const T& dato);
  void pop(void);
  const T& top(void) const;
  bool empty(void) const;
  bool full(void) const;
  void intercambio();

  // E/S
  std::ostream& write(std::ostream& = std::cout) const;

 private:
  int         top_;
  vector_t<T>    v_;
};


// operaciones
template<class T> void stack_v_t<T>::push(const T& dato) {
  assert(!full());
  v_[++top_] = dato;
}

template<class T> void stack_v_t<T>::pop(void) {
  assert(!empty());			
  top_--;
}

template<class T> const T& stack_v_t<T>::top(void) const {
  assert(!empty());
  return v_[top_];
}

template<class T> bool stack_v_t<T>::empty(void) const {
  return (top_ < 0);
}

template<class T> bool stack_v_t<T>::full(void) const {
  return (top_ == v_.get_size() - 1);
}

template<class T> void stack_v_t<T>::intercambio(void) {
  T aux = top();
  pop();
  T aux2 = top();
  pop();
  push(aux);
  push(aux2);
}

// E/S
template<class T> std::ostream& stack_v_t<T>::write(std::ostream& os) const {
  for(int i = top_; i >= 0; i--)
    os << " │ " << std::setw(2) << v_[i] << "  │" << std::endl;
  os << " └─────┘" << std::endl;
  return os;
}

}
// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
 rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);

 private: 
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T> const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) 	{
    char c = q.front();
    
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (isdigit(c)) {
      int i = c - '0';
      stack_.push(i);
      // poner código
      std::cout << " (es un dígito) " << std::endl
		<< "   Lo metemos en la pila..." << std::endl;
    } else {
      std::cout << " (es un operador)" << std::endl;
      // poner código
      operate_(c);
    }
  }
  // poner código
  return stack_.top();
}

template<class T> void rpn_t<T>::operate_(const char c) {
  assert(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'r' || c == 'l' || c == 'c');
  int i = stack_.top();
  stack_.pop();
  // poner código
  std::cout << "   Sacamos de la pila un operando: " << i << std::endl;
  int j = stack_.top();
  if (c != 'r' && c != 'l' && c != 'c') {
    stack_.pop();
    // poner código
    std::cout << "   Sacamos de la pila otro operando: " << j << std::endl;
  }
  
  switch (c) {
    case '+':
      stack_.push(j + i);
      break;
    // poner código resto de operadores
    case '-':
      stack_.push(j - i);
      break;
    
    case '*':
      stack_.push(j * i);
      break;
    
    case '/':
      stack_.push(j / i);
      break;
    
    // fase II
    case '^':
      stack_.push(pow(j, i));
      break;
    
    case 'r':
      stack_.push(sqrt(i));
      break;

  // fase III
    case 'l':
      stack_.push(log2(i));
      break;

    case 'c':
      stack_.push(i * i);
      break;
  }

  // poner código
  std::cout << "   Metemos en la pila el resultado: " << stack_.top() << std::endl;
}

 
#endif  // RPNT_H_

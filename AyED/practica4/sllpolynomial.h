// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  // poner el código aquí
  for (int i = v.get_size() - 1; i >= 0; i--) {
    if (IsNotZero(v.at(i))) {
      pair_double_t p(v.at(i), i);
      SllPolyNode* node = new SllPolyNode(p);
      push_front(node);
    }
  }
}


// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  SllPolyNode* aux{get_head()};
  // poner el código aquí
  while(aux != NULL) {
    int potencia{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    result += val * pow(x, potencia);
    aux = aux->get_next();
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;
  // poner el código aquí
  SllPolyNode* aux{get_head()};
  SllPolyNode* aux2{sllpol.get_head()};
  while (aux != NULL) {
    if (aux2 == NULL) {
      break;
    }
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    int inx2{aux2->get_data().get_inx()};
    double val2{aux2->get_data().get_val()};
    if (IsNotZero(val - val2) || inx != inx2) {
      differents = true;
      break;
    }
    aux = aux->get_next();
    aux2 = aux2->get_next();
  }
  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  SllPolyNode* aux{get_head()};
  SllPolyNode* aux2{sllpol.get_head()};
  SllPolyNode* prev;
  bool first = true;

  while (aux != NULL || aux2 != NULL) {
    // Si aux es NULL entonces ponemos un valor muy alto para el indice para que funcione el resto del código
    // y porque de otro modo aparece segmentation fault
    int inx = (aux != NULL) ? aux->get_data().get_inx() : 99999999;  
    double val = (aux != NULL) ? aux->get_data().get_val() : 0.0;
    int inx2 = (aux2 != NULL) ? aux2->get_data().get_inx() : 99999999;
    double val2 = (aux2 != NULL) ? aux2->get_data().get_val() : 0.0;
    
    if (inx == inx2) {
      val += val2;
      pair_double_t p(val, inx);
      SllPolyNode* node = new SllPolyNode(p);
      if (IsNotZero(val)) {
        if (first) { 
          sllpolsum.push_front(node);
          first = false;
        } else {
          sllpolsum.insert_after(prev, node);
        }
        prev = node;
      }
      aux = aux->get_next();
      aux2 = aux2->get_next();
    } 
    
    else if (inx < inx2) {
      pair_double_t p(val, inx);
      SllPolyNode* node = new SllPolyNode(p);
      
      if (first) { 
        sllpolsum.push_front(node);
        first = false;
      } else {
        sllpolsum.insert_after(prev, node);
      }

      prev = node;
      aux = aux->get_next();
    } 
    
    else {
      pair_double_t p(val2, inx2);
      SllPolyNode* node = new SllPolyNode(p);

      if (first) { 
        sllpolsum.push_front(node);
        first = false;
      } else {
        sllpolsum.insert_after(prev, node);
      }

      prev = node;
      aux2 = aux2->get_next();
    }
  }
}



#endif  // SLLPOLYNOMIAL_H_

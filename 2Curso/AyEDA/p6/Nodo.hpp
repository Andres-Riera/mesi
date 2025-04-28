#pragma once

template <class Key>
class NodoB {
 public:
  NodoB(Key dato) : dato_(dato), izq_(nullptr), der_(nullptr) {}
  void SetIzq(NodoB<Key>* izq) { izq_ = izq; }
  void SetDer(NodoB<Key>* der) { der_ = der; }
  NodoB<Key>*& GetIzq() { return izq_; }
  NodoB<Key>*& GetDer() { return der_; }
  Key GetDato() const { return dato_.getValue(); }
  NodoB<Key>& operator=(const NodoB<Key>& nodo) {
    if (this != &nodo) { 
      this->dato_ = nodo.GetDato();
      this->izq_ = nodo.GetIzq();
      this->der_ = nodo.GetDer();
    }
    return *this;
  }
 protected:
  Key dato_;
  NodoB<Key>* izq_;
  NodoB<Key>* der_;
};

template <class Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(Key dato) : NodoB<Key>(dato), bal_(0) {}
  NodoAVL(Key dato, short bal) : NodoB<Key>(dato), bal_(bal) {}
  NodoAVL(NodoB<Key>* &nodo) : bal_(0) {
    this->SetIzq(nodo->GetIzq());
    this->SetDer(nodo->GetDer());
    this->SetDato(nodo->GetDato());
  } 
  int GetBal() const { return bal_; }
  void SetBal(int bal) { bal_ = bal; }
 protected:
  short bal_;
};
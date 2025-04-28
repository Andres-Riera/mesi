#include "Arbol.hpp"

template <class Key>
class AVL : public AB<Key> {
 public:
  AVL() : AB<Key>() {}
  bool Insertar(Key dato) override;
  bool Buscar(Key dato) override; 
 private:
  void Rotacion_II(NodoAVL<Key>*& nodo);
  void Rotacion_DD(NodoAVL<Key>*& nodo);
  void Rotacion_ID(NodoAVL<Key>*& nodo);
  void Rotacion_DI(NodoAVL<Key>*& nodo);
  void ActualizarBalance(NodoAVL<Key>*& nodo);
  bool InsertaBal(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece);
  void InsertReBalanceaIzq(NodoAVL<Key>*& nodo, bool& crece);
  void InsertReBalanceaDer(NodoAVL<Key>*& nodo, bool& crece);
};

template <class Key>
bool AVL<Key>::Buscar(Key dato) {
  NodoB<Key>* actual = this->raiz_;
  while (actual != nullptr) {
    if (dato < actual->GetDato()) {
      actual = actual->GetIzq();
    } else if (dato > actual->GetDato()) {
      actual = actual->GetDer();
    } else {
      return true; // Encontrado
    }
  }
  return false; // No encontrado
}

template <class Key>
bool AVL<Key>::Insertar(Key dato) {
  NodoAVL<Key>* nuevo = new NodoAVL<Key>(dato);
  bool crece = false;
  if (InsertaBal(reinterpret_cast<NodoAVL<Key>*&>(this->raiz_), nuevo, crece)) {
    return true;
  } else {
    delete nuevo;
    return false; // Duplicado
  }
}

template <class Key>
bool AVL<Key>::InsertaBal(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
  if (nodo == nullptr) {
    nodo = nuevo;
    crece = true;
    return true;
  } else if (nuevo->GetDato() < nodo->GetDato()) {
    if(InsertaBal(reinterpret_cast<NodoAVL<Key>*&>(nodo->GetIzq()), nuevo, crece)) {
      if (crece) {
        InsertReBalanceaIzq(nodo, crece);
      }
    }
  } else if (nuevo->GetDato() > nodo->GetDato()) {
    if(InsertaBal(reinterpret_cast<NodoAVL<Key>*&>(nodo->GetDer()), nuevo, crece)) {
      if (crece) {
        InsertReBalanceaDer(nodo, crece);
      }
    }
  } else {
    return false; // Duplicado
  }
  return true;
}

template <class Key>
void AVL<Key>::InsertReBalanceaIzq(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->GetBal()) {
    case -1:
      nodo->SetBal(0);
      crece = false;
      break;
    case 0:
      nodo->SetBal(1);
      crece = true; // Sigue creciendo hacia la izquierda
      break;
    case 1:
      NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetIzq());
      if (nodo1->GetBal() == 1) {
        #ifdef TRAZA
        std::cout << "Desbalanceo "<< std::endl;
        this->recorreN();
        std::cout << "Rotacion II en nodo " <<  nodo->GetDato() << std::endl;
        #endif
        Rotacion_II(nodo);
      } else {
        #ifdef TRAZA
        std::cout << "Desbalanceo "<< std::endl;
        this->recorreN();
        std::cout << "Rotacion ID en nodo " <<  nodo->GetDato() << std::endl;
        #endif
        Rotacion_ID(nodo);
      }
      crece = false; // Después de rotar, ya no crece
      break;
  }
}


template <class Key>
void AVL<Key>::InsertReBalanceaDer(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->GetBal()) {
    case 1:
      nodo->SetBal(0);
      crece = false; // Se equilibra
      break;
    case 0:
      nodo->SetBal(-1);
      crece = true; // Sigue creciendo hacia la derecha
      break;
    case -1:
      NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetDer());
      if (nodo1->GetBal() == -1) {
        #ifdef TRAZA
        std::cout << "Desbalanceo "<< std::endl;
        this->recorreN();
        std::cout << "Rotacion DD en nodo " <<  nodo->GetDato() << std::endl;
        #endif
        Rotacion_DD(nodo);
      } else {
        #ifdef TRAZA
        std::cout << "Desbalanceo "<< std::endl;
        this->recorreN();
        std::cout << "Rotacion DI en nodo " <<  nodo->GetDato() << std::endl;
        #endif
        Rotacion_DI(nodo);
      }
      crece = false; // Después de rotar, ya no crece
      break;
  }
}


template <class Key>
void AVL<Key>::Rotacion_II(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetIzq());
  nodo->SetIzq(nodo1->GetDer());
  nodo1->SetDer(nodo);
  if (nodo1->GetBal() == 1) {
    nodo->SetBal(0);
    nodo1->SetBal(0);
  } else {
    nodo->SetBal(1);
    nodo1->SetBal(-1);
  }
  nodo = nodo1;
}

template <class Key>
void AVL<Key>::Rotacion_DD(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetDer());;
  nodo->SetDer(nodo1->GetIzq());
  nodo1->SetIzq(nodo);
  if (nodo1->GetBal() == -1) {
    nodo->SetBal(0);
    nodo1->SetBal(0);
  } else {
    nodo->SetBal(-1);
    nodo1->SetBal(1);
  }
  nodo = nodo1;
}

template <class Key>
void AVL<Key>::Rotacion_ID(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetIzq());
  NodoAVL<Key>* nodo2 = reinterpret_cast<NodoAVL<Key>*>(nodo1->GetDer());

  nodo1->SetDer(nodo2->GetIzq());
  nodo->SetIzq(nodo2->GetDer());

  nodo2->SetIzq(nodo1);
  nodo2->SetDer(nodo);

  switch (nodo2->GetBal()) {
    case -1:
      nodo1->SetBal(0);
      nodo->SetBal(1);
      break;
    case 1:
      nodo1->SetBal(-1);
      nodo->SetBal(0);
      break;
    case 0:
      nodo1->SetBal(0);
      nodo->SetBal(0);
      break;
  }
  nodo2->SetBal(0);
  nodo = nodo2;
}


template <class Key>
void AVL<Key>::Rotacion_DI(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*>(nodo->GetDer());
  NodoAVL<Key>* nodo2 = reinterpret_cast<NodoAVL<Key>*>(nodo1->GetIzq());

  nodo1->SetIzq(nodo2->GetDer());
  nodo->SetDer(nodo2->GetIzq());

  nodo2->SetDer(nodo1);
  nodo2->SetIzq(nodo);

  switch (nodo2->GetBal()) {
    case 1:
      nodo1->SetBal(0);
      nodo->SetBal(-1);
      break;
    case -1:
      nodo1->SetBal(1);
      nodo->SetBal(0);
      break;
    case 0:
      nodo1->SetBal(0);
      nodo->SetBal(0);
      break;
  }
  nodo2->SetBal(0);
  nodo = nodo2;
}



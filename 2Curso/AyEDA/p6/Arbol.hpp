#pragma once

#include <iostream>
#include <queue>

#include "Nodo.hpp"

template <class Key>
class AB {
 public:
  AB() : raiz_(nullptr) {}
  virtual bool Insertar(Key dato) = 0;
  virtual bool Buscar(Key dato) = 0;
  
  void Inorden() const {
    InordenRec(raiz_);
    std::cout << std::endl;
  }

  void recorreN() const {
    std::queue<NodoB<Key>*> cola;
    if (raiz_ != nullptr) {
      cola.push(raiz_);
    } else {
      std::cout << "Nivel 0: [.]" << std::endl;
      return;
    }
    int nivel = 0;
    while (!cola.empty()) {
      int tam = cola.size();
      std::cout << "Nivel " << nivel << ": ";
      for (int i = 0; i < tam; ++i) {
        NodoB<Key>* actual = cola.front();
        cola.pop();
        if (actual != nullptr) {
          std::cout << "[" << actual->GetDato() << "]";
          cola.push(actual->GetIzq());
          cola.push(actual->GetDer());
        } else {
          std::cout << "[.]";
          cola.push(nullptr);
          cola.push(nullptr);
        }
      }
      std::cout << std::endl;
      ++nivel;
      bool todosNulos = true;
      for (size_t i = 0; i < cola.size(); ++i) {
        NodoB<Key>* nodo = cola.front();
        cola.pop();
        cola.push(nodo);
        if (nodo != nullptr) {
          todosNulos = false;
        }
      }
      if (todosNulos) {
        break;
      }
    }
  }

  protected:
   NodoB<Key>* raiz_;
  private:
   void InordenRec(NodoB<Key>* nodo) const {
    if (nodo != nullptr) {
      InordenRec(nodo->GetIzq());
      std::cout << nodo->GetDato() << " ";
      InordenRec(nodo->GetDer());
    }
   }
};

template <class Key>
class ABB : public AB<Key> {
 public:
  ABB() : AB<Key>() {}
  bool Insertar(Key dato) override;
  bool Buscar(Key dato) override;
};

template <class Key>
bool ABB<Key>::Insertar(Key dato) {
  if (this->raiz_ == nullptr) {
    this->raiz_ = new NodoB<Key>(dato);
    return true;
  }
  NodoB<Key>* actual = this->raiz_;
  NodoB<Key>* padre = nullptr;
  while (actual != nullptr) {
    padre = actual;
    if (dato < actual->GetDato()) {
      actual = actual->GetIzq();
    } else if (dato > actual->GetDato()) {
      actual = actual->GetDer();
    } else {
      return false; // Duplicado
    }
  }
  if (dato < padre->GetDato()) {
    padre->SetIzq(new NodoB<Key>(dato));
  } else {
    padre->SetDer(new NodoB<Key>(dato));
  }
  return true;
}

template <class Key>
bool ABB<Key>::Buscar(Key dato) {
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
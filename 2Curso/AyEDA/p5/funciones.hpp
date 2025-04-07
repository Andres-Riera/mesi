#include <vector>
#include <algorithm>

#include "Sequence.hpp"

template <class Key>
void Insercion(StaticSequence<Key>& secuencia, unsigned size) {
  if (size <= 1) return;
  for (auto i = 1; i < size; i++) {
    Key key = secuencia[i];
    int j = i - 1;
    while (j >= 0 && secuencia[j] > key) {
      // desplazar a la derecha
      secuencia[j + 1] = secuencia[j];
      j--;
    }
    secuencia[j + 1] = key;
    #ifdef TRAZA
    std::cout << "Iteración " << i << ":\n";
    writeSequence(secuencia);
    #endif
  }
}

template <class Key>
void Sacudida(StaticSequence<Key>& secuencia, unsigned size) {
  if (size <= 1) return;
  int ini = 1; 
  int fin = size - 1; 
  int cam = size;
  #ifdef TRAZA
  unsigned pasadas = 0;
  #endif
  while (ini < fin){
   for (int j = fin; j >= ini; j--) {
      if (secuencia[j] < secuencia[j-1]) {
        std::swap(secuencia[j-1],secuencia[j]);
        cam = j;
      } 
    }
    #ifdef TRAZA
    std::cout << "Pasada " << ++pasadas << ":\n";
    writeSequence(secuencia);
    #endif
    ini = cam + 1;
    for (int j = ini; j <= fin; j++) {
      if (secuencia[j] < secuencia[j-1]) {
        std::swap(secuencia[j-1],secuencia[j]);
        cam = j;
      }
    }
    #ifdef TRAZA
    std::cout << "Pasada " << ++pasadas << ":\n";
    writeSequence(secuencia);
    #endif
    fin = cam - 1;
  }
}

template <class Key>
void Quicksort(StaticSequence<Key>& secuencia, unsigned inicio, unsigned fin, unsigned iteraciones = 0) {
  if (inicio >= fin) return;
  unsigned i = inicio;
  unsigned f = fin;
  Key pivote = secuencia[(inicio + fin) / 2];
  while (i <= f) {
    while (secuencia[i] < pivote) ++i;
    while (secuencia[f] > pivote) --f;
    if (i <= f) {
      std::swap(secuencia[i], secuencia[f]);
      i++;
      f--;
    }
    #ifdef TRAZA
    std::cout << "Iteración " << ++iteraciones << "\n";
    writeSequence(secuencia);
    #endif
  }
  if (inicio < f) Quicksort(secuencia, inicio, f, iteraciones);
  if (i < fin) Quicksort(secuencia, i, fin, iteraciones);
}

template <class Key>
void Quicksort(StaticSequence<Key>& secuencia, unsigned size) {
  if (size <= 1) return;
  if (size > 1) Quicksort(secuencia, 0, size - 1);
}

template <class Key>
void baja(unsigned i, StaticSequence<Key>& secuencia, unsigned size) {
  while (2 * i <= size - 1) {
    unsigned h;
    unsigned h1 = 2 * i;
    unsigned h2 = h1 + 1;
    if (h1 == size - 1) h = h1;
    else if (secuencia[h1] > secuencia[h2]) h = h1;
    else h = h2;
    if (secuencia[h] <= secuencia[i]) break;
    else {
      std::swap(secuencia[i], secuencia[h]);
      i = h;
    }
  }
}

template <class Key>
void Heapsort(StaticSequence<Key>& secuencia, unsigned size) {
  if (size <= 1) return;
  #ifdef TRAZA
  unsigned iteraciones = 0;
  #endif
  for (int i = size / 2; i > 0; i--) {
    baja(i, secuencia, size);
    #ifdef TRAZA
    std::cout << "Iteración " << iteraciones + 1<< ":\n";
    writeSequence(secuencia);
    iteraciones++;
    #endif
  }
  for (int i = size - 1; i > 1; i--) {
    std::swap(secuencia[1], secuencia[i]);
    baja(1, secuencia, static_cast<unsigned>(i) - 1);
    #ifdef TRAZA
    std::cout << "Iteración " << iteraciones + 1<< ":\n";
    writeSequence(secuencia);
    iteraciones++;
    #endif
  }
}

template <class Key>
void Shellsort(StaticSequence<Key>& secuencia, unsigned size) {
  if (size <= 1) return;
  #ifdef TRAZA
  unsigned iteraciones = 0;
  #endif
  for (unsigned gap = size / 2; gap > 0; gap /= 2) {
    for (unsigned i = gap; i < size; ++i) {
      Key temp = secuencia[i];
      int j = i;
      while (j >= gap && secuencia[j - gap] > temp) {
        secuencia[j] = secuencia[j - gap];
        j -= gap;
      }
      secuencia[j] = temp;
      #ifdef TRAZA
      std::cout << "Iteración " << iteraciones + 1 << ":\n";
      writeSequence(secuencia);
      iteraciones++;
      #endif
    }
  }
}
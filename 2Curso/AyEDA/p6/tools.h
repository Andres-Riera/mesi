#include <thread>
#include <chrono>
#include <fstream>
#include <string>

#include "AVL.hpp"
#include "NIF.hpp"

void Usage(char* argv[]) {
  std::cout << "Uso: " << argv[0] << " opciones\n";
  std::cout << "Opciones:\n-ab <abb|avl>, para indicar el tipo de árbol con el que se va a trabajar\n";
  std::cout << "-init <i> [s] [f]\n";
  std::cout << "i=manual\n";
  std::cout << "i=random [s], s es el número de elementos a generar\n";
  std::cout << "i=file [s] [f] , s es el número de elementos a generar\n";
  std::cout << "                 f es el nombre del fichero de entrada\n";
}

template <class Key, template <class> class Arbol>
void Randomize(Arbol<Key>& arbol, unsigned size) {
  arbol.recorreN();
  std::cout << std::endl;
  for (unsigned i = 0; i < size; i++) {
    Key valor;
    std::cout << "Insertar: " << valor << std::endl;
    arbol.Insertar(valor);
    arbol.recorreN();
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

template <class Key, template <class> class Arbol>
void Fichero(Arbol<Key>& arbol, std::ifstream& file, unsigned size) {
  for (unsigned i = 0; i < size; i++) {
    long valor;
    file >> valor;
    Key value(valor);
    std::cout << "Insertar: " << valor << std::endl;
    arbol.Insertar(value);
  }
}

template <class Key, template <class> class Arbol>
void Menu(Arbol<Key>& arbol, short opcion) {
  long valor;
  Key value;
  switch (opcion) {
    case 1:
      std::cout << "Insertar: ";
      std::cin >> valor;
      value = Key(valor);
      arbol.Insertar(value);
      arbol.recorreN();
      break;
    case 2:
      std::cout << "Buscar: ";
      std::cin >> valor;
      value = Key(valor);
      if (arbol.Buscar(value)) {
        std::cout << "Elemento encontrado." << std::endl;
      } else {
        std::cout << "Elemento no encontrado." << std::endl;
      }
      break;
    case 3:
      arbol.Inorden();
      break;
    default:
      std::cerr << "Opción no válida." << std::endl;
      break;
  }
}

void PrintMenu() {
  std::cout << "Opciones:\n";
  std::cout << "[0] Salir\n";
  std::cout << "[1] Insertar\n";
  std::cout << "[2] Buscar\n";
  std::cout << "[3] Mostrar árbol en inorden\n";
}


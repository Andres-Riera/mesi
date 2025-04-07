#include <thread>
#include <chrono>
#include <fstream>
#include <string>


#include "SortMethods.hpp"
#include "NIF.hpp"

template <class Key>
void Randomize(StaticSequence<Key>& secuencia, unsigned size) {
  for (unsigned i = 0; i < size; i++) {
    Key valor;
    secuencia[i] = valor;
    std::cout << "Valor aleatorio generado: " << secuencia[i].getValue() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

template <class Key, template <class> class Method>
void Ordenar(Method<Key>& metodo) {
  metodo.Sort();
}

void Usage(char* argv[]) {
  std::cout << "Uso: " << argv[0] << " opciones\n";
  std::cout << "Opciones:\n-size <tamaño>\n-metodo <método>\n-entrada <entrada> fichero\n";
  std::cout << "Métodos disponibles:\n";
  std::cout << "1. Inserción\n";
  std::cout << "2. Sacudida\n";
  std::cout << "3. Quicksort\n";
  std::cout << "4. Heapsort\n";
  std::cout << "5. Shellsort\n";
  std::cout << "Tipos de entrada:\n";
  std::cout << "0. Manual\n";
  std::cout << "1. Aleatoria\n";
  std::cout << "2. Fichero\n";
}

int main(int argc, char* argv[]) {
  unsigned size = 5;
  unsigned metodo = 1;
  unsigned entrada = 1;
  std::ifstream file;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-size") {
      size = std::stoul(argv[++i]);
    } else if (arg == "-metodo") {
      metodo = std::stoul(argv[++i]);
    } else if (arg == "-entrada") {
      entrada = std::stoul(argv[++i]);
      if (entrada == 2) {
        file.open(argv[++i]);
        if (!file.is_open()) {
          std::cerr << "Error al abrir el fichero: " << argv[i] << std::endl;
          return 1;
        }
      }
    } else{
      Usage(argv);
      return 1;
    } 
  }
  StaticSequence<nif> secuencia(size);
  switch (entrada) {
    case 0:
      for (unsigned i = 0; i < size; i++) {
        long valor;
        std::cout << "Introduzca el NIF (8 dígitos): ";
        std::cin >> valor;
        try {
          nif nifValue(valor);
          secuencia[i] = nifValue;
        } catch (const std::invalid_argument& e) {
          std::cerr << "Error: " << e.what() << std::endl;
          return 1;
        }
      }
      break;
    case 1:
      std::cout << "Creando secuencia de tamaño " << size << "..." << std::endl;
      Randomize(secuencia, size);
      break;
    case 2:
      if (!file.is_open()) {
        std::cerr << "Error al abrir el fichero." << std::endl;
        return 1;
      } else {
        long valor;
        unsigned i = 0;
        while (file >> valor) {
          try {
            nif nifValue(valor);
            secuencia[i] = nifValue;
            i++;
          } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
          }
        }
      }
      break;
    default:
      Usage(argv);
      return 1;
  }
  std::cout << "Secuencia inicial:\n";
  writeSequence(secuencia);

  switch (metodo){
    case 1: {
      std::cout << "Método de ordenación: Inserción\n";
      InsertionSort<nif> metodo(&secuencia);
      Ordenar(metodo);
      break;
    }
    case 2: {
      std::cout << "Método de ordenación: Sacudida\n";
      ShakeSort<nif> metodo(&secuencia);
      Ordenar(metodo);
      break;
    }
    case 3: {
      std::cout << "Método de ordenación: Quicksort\n";
      QuickSort<nif> metodo(&secuencia);
      Ordenar(metodo);
      break;
    }
    case 4: {
      std::cout << "Método de ordenación: Heapsort\n";
      HeapSort<nif> metodo(&secuencia);
      Ordenar(metodo);
      break;
    }
    case 5: {
      std::cout << "Método de ordenación: Shellsort\n";
      ShellSort<nif> metodo(&secuencia);
      Ordenar(metodo);
      break;
    }
    default:
      std::cerr << "Método de ordenación no válido." << std::endl;
      Usage(argv);
      return 1;
  }
  std::cout << "Secuencia ordenada:\n";
  writeSequence(secuencia);
  if (entrada == 2) {
    file.close();
  }
  return 0;
}
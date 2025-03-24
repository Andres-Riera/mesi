#include <iostream>
#include <string>
#include <stdexcept>

#include "HashTable.hpp"
#include "NIF.hpp"

// Función para mostrar el uso correcto del programa
void showUsage(const std::string& programName) {
  std::cerr << "Uso: " << programName << " -ts <tamaño> -fd <función dispersión> "
            << "-hash <open|close> [-bs <tamaño bloque>] [-fe <función exploración>]\n";
  std::cerr << "Opciones:\n"
            << "  -ts <tamaño>          Tamaño de la tabla hash.\n"
            << "  -fd <función>         Función de dispersión (1: módulo, 2: suma, 3: pseudoaleatoria).\n"
            << "  -hash <open|close>    Técnica de dispersión (abierta o cerrada).\n"
            << "  -bs <tamaño bloque>   Tamaño del bloque (solo para dispersión cerrada).\n"
            << "  -fe <función>         Función de exploración (1: lineal, 2: cuadrática, 3: doble dispersión, 4: redispersión).\n";
}

int main(int argc, char* argv[]) {
  // 1. Parsear los argumentos de la línea de comandos
  unsigned tableSize = 0;
  int dispersionFunctionCode = 0;
  std::string hashType;
  unsigned blockSize = 1;
  int explorationFunctionCode = 0;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ts" && i + 1 < argc) {
      tableSize = std::stoul(argv[++i]);
    } else if (arg == "-fd" && i + 1 < argc) {
      dispersionFunctionCode = std::stoi(argv[++i]);
    } else if (arg == "-hash" && i + 1 < argc) {
      hashType = argv[++i];
    } else if (arg == "-bs" && i + 1 < argc) {
      blockSize = std::stoul(argv[++i]);
    } else if (arg == "-fe" && i + 1 < argc) {
      explorationFunctionCode = std::stoi(argv[++i]);
    } else {
      showUsage(argv[0]);
      return 1;
    }
  }

  // Validar argumentos obligatorios
  if (tableSize == 0 || dispersionFunctionCode == 0 || hashType.empty()) {
    showUsage(argv[0]);
    return 1;
  }

  // 2. Crear la función de dispersión
  DispersionFunction<nif>* dispersionFunction = nullptr;
  switch (dispersionFunctionCode) {
    case 1:
      dispersionFunction = new ModuloDispersion<nif>(tableSize);
      break;
    case 2:
      dispersionFunction = new SumDispersion<nif>(tableSize);
      break;
    case 3:
      dispersionFunction = new PseudoRandomDispersion<nif>(tableSize);
      break;
    default:
      std::cerr << "Código de función de dispersión no válido.\n";
      return 1;
  }

  // 3. Crear la función de exploración (solo para dispersión cerrada)
  ExplorationFunction<nif>* explorationFunction = nullptr;
  if (hashType == "close") {
    switch (explorationFunctionCode) {
      case 1:
        explorationFunction = new LinearExploration<nif>();
        break;
      case 2:
        explorationFunction = new QuadraticExploration<nif>();
        break;
      case 3:
        explorationFunction = new DoubleExploration<nif>(*dispersionFunction);
        break;
      case 4:
        explorationFunction = new ReDispersionExploration<nif>(*dispersionFunction, tableSize);
        break;
      default:
        std::cerr << "Código de función de exploración no válido.\n";
        return 1;
    }
  }

  // 4. Crear la tabla hash
  HashTable<nif, StaticSequence<nif>>* staticHashTable = nullptr;
  HashTable<nif, DynamicSequence<nif>>* dynamicHashTable = nullptr;

  if (hashType == "open") {
    dynamicHashTable = new HashTable<nif, DynamicSequence<nif>>(tableSize, *dispersionFunction);
  } else if (hashType == "close") {
    staticHashTable = new HashTable<nif, StaticSequence<nif>>(tableSize, *dispersionFunction, explorationFunction, blockSize);
  } else {
    std::cerr << "Tipo de dispersión no válido. Use 'open' o 'close'.\n";
    return 1;
  }

  // 5. Menú interactivo
  int option;
  while (true) {
    std::cout << "\nMenú:\n"
              << "1. Insertar NIF\n"
              << "2. Buscar NIF\n"
              << "3. Salir\n"
              << "Seleccione una opción: ";
    std::cin >> option;

    if (option == 1) {
      long nifValue;
      std::cout << "Introduzca el NIF (8 dígitos): ";
      std::cin >> nifValue;
      try {
        nif newNif(nifValue);
        if (dynamicHashTable) {
          unsigned position;
          if (dynamicHashTable->insert(newNif, position)) {
            std::cout << "NIF insertado correctamente en la posición " << position << ".\n";
          } else {
            std::cout << "No se pudo insertar el NIF.\n";
          }
        } else if (staticHashTable) {
          unsigned position;
          if (staticHashTable->insert(newNif, position)) {
            std::cout << "NIF insertado correctamente en la posición " << position << ".\n";
          } else {
            std::cout << "No se pudo insertar el NIF.\n";
          }
        }
      } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
      }
    } else if (option == 2) {
      long nifValue;
      std::cout << "Introduzca el NIF a buscar (8 dígitos): ";
      std::cin >> nifValue;
      try {
        nif searchNif(nifValue);
        if (dynamicHashTable) {
          unsigned position;
          if (dynamicHashTable->search(searchNif, position)) {
            unsigned position;
            std::cout << "NIF encontrado en la posición" << position << ".\n";
          } else {
            std::cout << "NIF no encontrado.\n";
          }
        } else if (staticHashTable) {
          unsigned position;
          if (staticHashTable->search(searchNif, position)) {
            std::cout << "NIF encontrado en la posición " << position << ".\n";
          } else {
            std::cout << "NIF no encontrado.\n";
          }
        }
      } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
      }
    } else if (option == 3) {
      break;
    } else {
      std::cout << "Opción no válida.\n";
    }
  }

  // Liberar memoria
  delete dispersionFunction;
  delete explorationFunction;
  delete dynamicHashTable;
  delete staticHashTable;

  return 0;
}
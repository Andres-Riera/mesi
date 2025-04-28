#include "tools.h"

int main(int argc, char* argv[]) {
  unsigned size = 8;
  short metodo = 1;
  bool avl = true;
  std::ifstream file;
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-ab") {
      std::string tipo = argv[++i];
      if (tipo == "avl") {
        avl = true;
      } else if (tipo == "abb") {
        avl = false;
      } else {
        std::cerr << "Tipo de árbol no válido." << std::endl;
        Usage(argv);
        return 1;
      }
    } else if (arg == "-init") {
      std::string initType = argv[++i];
      if (initType == "manual") {
        metodo = 0;
      } else if (initType == "random") {
        size = std::stoul(argv[++i]);
        metodo = 1;
      } else if (initType == "file") {
        metodo = 2;
        size = std::stoul(argv[++i]);
        file.open(argv[++i]);
        if (!file.is_open()) {
          std::cerr << "Error al abrir el fichero: " << argv[i] << std::endl;
          return 1;
        }
      } else {
        Usage(argv);
        return 1;
      }
    } else {
      Usage(argv);
      return 1;
    }
  }

  if (avl) {
    AVL<nif> arbolAVL;
    if (metodo == 1) {
      Randomize(arbolAVL, size);
    } else if (metodo == 2) {
      Fichero(arbolAVL, file, size);
    }
    arbolAVL.recorreN();
    while (true) {
      PrintMenu();
      short opcion;
      std::cin >> opcion;
      if (opcion == 0) {
        return 0;
      } else if (opcion == 1 || opcion == 2 || opcion == 3) {
        Menu(arbolAVL, opcion);
      } else {
        std::cerr << "Opción no válida." << std::endl;
      }
    }
    
  } else {
    ABB<nif> arbolABB;
    if (metodo == 1) {
      Randomize(arbolABB, size);
    } else if (metodo == 2) {
      Fichero(arbolABB, file, size);
    }
    arbolABB.recorreN();
    while (true) {
      PrintMenu();
      short opcion;
      std::cin >> opcion;
      if (opcion == 0) {
        return 0;
      } else if (opcion == 1 || opcion == 2 || opcion == 3) {
        Menu(arbolABB, opcion);
      } else {
        std::cerr << "Opción no válida." << std::endl;
      }
    }
  }
  return 0;
}
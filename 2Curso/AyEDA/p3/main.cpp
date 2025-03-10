#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include <stdexcept>

#include "BigNumber.hpp"

template <unsigned char Base>
void ProcesarArchivo(std::ifstream& file) {
  std::map<std::string, BigNumber<Base>*> board;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string etiqueta, operacion;
    iss >> etiqueta >> operacion;
    if (operacion == "=") {
      std::string numero;
      iss >> numero;
      board[etiqueta] = BigNumber<Base>::create(numero.c_str());
      std::cout << etiqueta << " = " << numero << std::endl;
    } else if (operacion == "?") {
      std::stack<BigNumber<Base>*> pila;
      std::string token;
      while (iss >> token) {
        if (board.find(token) != board.end()) {
          pila.push(board[token]);
        } else if (token == "+") {
          if (pila.size() < 2) throw std::runtime_error("Not enough operands for +");
          auto op1 = pila.top(); pila.pop();
          auto op2 = pila.top(); pila.pop();
          auto* result = &op1->add(*op2);
          pila.push(result);
        } else if (token == "-") {
          if (pila.size() < 2) throw std::runtime_error("Not enough operands for -");
          auto op1 = pila.top(); pila.pop();
          auto op2 = pila.top(); pila.pop();
          auto* result = &op1->subtract(*op2);
          pila.push(result);
        } else if (token == "*") {
          if (pila.size() < 2) throw std::runtime_error("Not enough operands for *");
          auto op1 = pila.top(); pila.pop();
          auto op2 = pila.top(); pila.pop();
          auto* result = &op1->multiply(*op2);
          pila.push(result);
        } else if (token == "/") {
          if (pila.size() < 2) throw std::runtime_error("Not enough operands for /");
          auto op1 = pila.top(); pila.pop();
          auto op2 = pila.top(); pila.pop();
          auto* result = &op1->divide(*op2);
          pila.push(result);
        } else {
          throw std::invalid_argument("Operación no soportada: " + token);
        }
      }
      if (!pila.empty()) {
        std::cout << etiqueta << " = " << *pila.top() << std::endl;
      }
    }
  }
  for (auto& pair : board) {
    delete pair.second;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero>" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "No se pudo abrir el archivo: " << argv[1] << std::endl;
    return 1;
  }
  std::string trash;
  int base;
  file >> trash >> trash >> base;
  if (base == 2) {
    std::cout << "Base = 2" << std::endl;
    ProcesarArchivo<2>(file);
  } else if (base == 8) {
    std::cout << "Base = 8" << std::endl;
    ProcesarArchivo<8>(file);
  } else if (base == 10) {
    std::cout << "Base = 10" << std::endl;
    ProcesarArchivo<10>(file);
  } else if (base == 16) {
    std::cout << "Base = 16" << std::endl;
    ProcesarArchivo<16>(file);
  } else {
    std::cerr << "Base no soportada." << std::endl;
    return 1;
  }
  file.close();
  return 0;
}
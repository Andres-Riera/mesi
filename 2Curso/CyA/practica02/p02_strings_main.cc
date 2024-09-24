// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo p02_strings_main.cc: programa cliente.
// Contiene la función main del proyecto que usa las clases Alfabeto y Cadena
// para operar con ficheros usando los métodos de la clase Cadena


#include <iostream>
#include <fstream>


#include "cadena.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream archivo_entrada {argv[1]};
  if (!archivo_entrada) {
    std::cerr << "Error al abrir el archivo de entrada.\n";
    return 1;
  }
  std::string nombre_salida {argv[2]};
  std::ofstream archivo_salida(nombre_salida);
  int operacion {std::stoi(argv[3])};
  std::string aux;
  std::string alfabeto;
  while (archivo_entrada >> aux >> alfabeto) {
    Cadena chain {aux, alfabeto};
    switch (operacion) {
      case 1:
        archivo_salida << chain.mostrar_alfabeto();
        break;
      case 2:
        archivo_salida << chain.get_longitud();
        break;
      case 3:
        archivo_salida << chain.inversa();
        break;
      case 4:
        chain.prefijos(archivo_salida);
        break;
      case 5:
        chain.sufijos(archivo_salida);
        break;
      default:
        break;
    }
    archivo_salida << std::endl;
  }

  return 0;
}
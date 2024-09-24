// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo tools.h
// Contiene la función Usage


#include <iostream>

// Esta función se encarga de verificar que los parámetros sean correctos y proporciona ayuda al usuario en caso de que
// haya algún error con estos
void Usage(int argc, char *argv[]) {
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << "El programa recibe como parámetros un archivo de entrada, el nombre del archivo de salida y un código de operación." 
                << std::endl;
      std::cout << "El archivo de entrada deberá contener una cadena seguida de su respectivo alfabeto." << std::endl;
      std::cout << "En el archivo de salida se escribirá lo que indique el código de operación." << std::endl;
      std::cout << "Códigos de operación:\n1: Alfabeto de todas las cadenas\n2: Longitud de las cadenas\n3: Inversa de las cadenas\n4: "
                << "Prefijos de las cadenas\n5: Sufijos de las cadenas" << std::endl;

      exit(EXIT_SUCCESS);
    }
  }

  if (argc != 4) {
    std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt opcode" << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
}
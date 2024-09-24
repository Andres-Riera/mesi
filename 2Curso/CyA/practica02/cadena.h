// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo cadena.h
// Contiene la declaración de la clase Cadena

#pragma once

#include <fstream>
#include <vector>

#include "alfabeto.h"

class Cadena {
 public:
  Cadena() = default; // Constructor por defecto
  Cadena(std::string cadena, std::string alphabet); // Constructor a partir de dos strings
  Cadena(std::string cadena, Alfabeto alphabet); // Constructor a partir de una string y un Alfabeto
  Alfabeto mostrar_alfabeto() {return alfabeto_;} // Devuelve el alfabeto al que pertenece la cadena
  int get_longitud() {return longitud_; } // Devuelve la longitud de la cadena
  Cadena inversa(); // Devuelve la inversa de la cadena
  void prefijos(std::ofstream& archivo); // Escribe en el archivo de salida los prefijos de la cadena
  void sufijos(std::ofstream& archivo); // Escribe en el archivo de salida los sufijos de la cadena
  friend std::ostream& operator<<(std::ostream& out, const Cadena& a); // Sobrecarga del operador de salida para la clase Cadena

 private:
  std::vector<char> cadena_;
  Alfabeto alfabeto_;
  int longitud_;
};
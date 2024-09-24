// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Andrés David Riera Rivera
// Correo: alu0101618654@ull.edu.es
// Fecha: 17/09/2024
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la función main del proyecto que usa las clases X e Y
// Historial de revisiones
// 21/09/2024 - Creación (primera versión) del código

#pragma once

#include "alfabeto.h"
#include "cadena.h"

class Lenguaje {
 public:
  Lenguaje();
 private:
  std::set<Cadena> lenguaje_;
  Alfabeto alphabet_;
};
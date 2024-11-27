#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <expected>
#include <string_view>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "safemap.h"



enum class parse_args_errors {
  missing_argument,
  unknown_option,
};

struct program_options {
  bool show_help = false;
  bool verbose = false;
  std::string output_filename;

  std::vector<std::string> additional_args;
};


std::expected<program_options, parse_args_errors> parse_args(int argc, char* argv[]) {
  std::vector<std::string_view> args(argv + 1, argv + argc);
  program_options options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-h" || *it == "--help") {
      options.show_help = true;
    }
    else if (*it == "-v" || *it == "--verbose") {
      options.verbose = true;
    }
    else if (*it == "-p" || *it == "--puerto") {
      options.verbose = true;
    }
    /*else if (*it == "-o" || *it == "--output") {
      if (++it != end) {
        options.output_filename = *it;
      }
      else {
        return std::unexpected(parse_args_errors::missing_argument);
      }
    }
    // Procesar otras opciones...
    else if(!it->starts_with("-")) {
      options.additional_args.push_back(std::string(*it));
    }*/
    else {
      if (it != end) {
        options.output_filename = *it;
      }
      else {
        return std::unexpected(parse_args_errors::unknown_option);
      }
    }
  }
  return options;
}

std::expected<SafeMap, int> read_all(const std::string& path) {
  // Convertir std::string a C-string (const char*)
  const char* cpath = path.c_str();
  // Abrir el archivo en modo solo lectura
  int fd = open(cpath, O_RDONLY);
  if (fd < 0) {
    // Error al abrir el archivo
    return std::unexpected(errno);
  }

  // Para mapear una archivo completo es necesario conocer su tamaño.
  // Una forma es usar fstat() y otra es usar lseek().
  // La función lseek() sirve para mover el puntero de lectura/escritura de un archivo y retorna la posición
  // a la que se ha movido. Por tanto, si se mueve al final del archivo, se obtiene el tamaño de este.
  int file_size = lseek(fd, 0, SEEK_END);

  // Se mapea el archivo completo en memoria para solo lectura y de forma privada.
  void* mem = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (mem == MAP_FAILED) {
    // Error al mapear el archivo...
    close(fd);
    return std::unexpected(errno);
  }

  // Opcionalmente, se puede cerrar el descriptor del archivo si ya no se necesita.
  close(fd);

  std::string_view aux(static_cast<char*>(mem), file_size);
  SafeMap result(aux);

  // Retornar el contenido del archivo como std::string_view
  return result;
}

void send_response(std::string header, std::string_view body = {}) {
  std::cout << header << std::endl;
  std::cout << body << std::endl;
}
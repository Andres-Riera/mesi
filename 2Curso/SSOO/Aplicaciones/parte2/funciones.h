#pragma once

#include <sys/socket.h> 
#include <netinet/ip.h>
#include <sys/un.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <cstdlib>


#include "safemap.h"

#define ESUCCESS 0

enum class parse_args_errors {
  missing_argument,
  unknown_option,
};

struct program_options {
  bool show_help = false;
  bool verbose = false;
  bool b_puerto = false;
  uint16_t puerto = 8080;

  std::string output_filename;
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
      options.b_puerto = true;
      if (++it != end) {
        try {
          int port = std::stoi(std::string(*it));
          if (port < 1 || port > 65535) {
            return std::unexpected(parse_args_errors::missing_argument); // Puerto inválido
          }
          options.puerto = static_cast<uint16_t>(port);
        } catch (const std::exception&) {
          return std::unexpected(parse_args_errors::missing_argument);
        }
      }
      else {
        return std::unexpected(parse_args_errors::missing_argument);
      }
    }
    else {
      if (it + 1 == end) {
        options.output_filename = *it;
      }
      else {
        return std::unexpected(parse_args_errors::unknown_option);
      }
    }
  }
  if (options.output_filename == "" && options.show_help == 0) {
    return std::unexpected(parse_args_errors::missing_argument);
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

int send_response(const SafeFD& socket, std::string header, std::string_view body = {}) {
  std::string message_text = header + "\n" + std::string(body);
  int mensaje_enviado = send(socket.get(), message_text.data(), message_text.size(), 0);
  if (mensaje_enviado < 0) {
    // Error al enviar el mensaje...
    return errno;
  }

  return ESUCCESS;
}

std::string getenv(const std::string& name) {
  char* value = getenv(name.c_str());
  if (value) {
  return std::string(value);
  }
  else {
  return std::string();
  }
}

std::expected<SafeFD, int> make_socket(uint16_t port){
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    // Error al crear el socket...
    return std::unexpected(errno);
  }

  sockaddr_in local_address{};                            // <1>
  local_address.sin_family = AF_INET;                     // <2>
  local_address.sin_addr.s_addr = htonl(INADDR_ANY);      // <3>
  local_address.sin_port = htons(port);                      // <4>

  int result = bind(
    sock_fd,                                            // <5>
    reinterpret_cast<const sockaddr*>(&local_address),  // <6>
	  sizeof(local_address)                               // <7>
  );
  if (result < 0) {
    // Error al asignar una dirección...
    close(sock_fd);
    return std::unexpected(errno);
  }

  return SafeFD(sock_fd);
}

int listen_connection(const SafeFD& socket) {
  int result = listen(socket.get(), 1);
  if (result < 0) {
    // Error al poner el socket en modo de escucha...
    return errno;
  }
  return ESUCCESS;
}

std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr) {
  socklen_t client_addr_length = sizeof(client_addr);

  // Aceptar la primera conexión que llegue
  int new_fd = accept(socket.get(), reinterpret_cast<sockaddr*>(&client_addr), &client_addr_length);
  if (new_fd < 0) {
    // Error al aceptar la conexión...
    return std::unexpected(errno);
  }
  return SafeFD(new_fd);
}
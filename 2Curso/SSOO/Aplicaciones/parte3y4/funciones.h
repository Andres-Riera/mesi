#pragma once

#include <cassert>
#include <sys/socket.h> 
#include <netinet/ip.h>
#include <sys/un.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <cstdlib>
#include <sstream>


#include "safemap.h"
#include "exec_environment.h"

#define ESUCCESS 0

enum class parse_args_errors {
  missing_argument,
  unknown_option,
};

struct program_options {
  bool show_help = false;
  bool verbose = false;
  bool b_puerto = false;
  bool b_ruta = false;

  bool b_echo = false;

  std::string ruta;
  uint16_t puerto = 8080;
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
    else if (*it == "-e" || *it == "--echo") { // modificación
      options.b_echo = true;
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

    else if (*it == "-b" || *it == "--base") {
      options.b_ruta = true;
      if (++it != end) {
        if(!it->starts_with("-")) {
          options.ruta = std::string(*it);
        }
        else {
        return std::unexpected(parse_args_errors::missing_argument);
        }
      }
      else {
        return std::unexpected(parse_args_errors::missing_argument);
      }
    }

    else {
     return std::unexpected(parse_args_errors::unknown_option);
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
    int error = errno;
    close(fd);
    return std::unexpected(error);
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
    int error = errno;
    close(fd);
    return std::unexpected(error);
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

std::expected<std::string, int> receive_request(const SafeFD& socket, size_t max_size) {
  std::string message_text;
  message_text.resize(max_size);
  int bytes_read = recv(socket.get(), message_text.data(), message_text.size(), 0);
  if (bytes_read < 0) {
    // Error al recibir el mensaje...
    return std::unexpected(errno);
  }
  return std::string(message_text);
}

struct execute_program_error {
  int exit_code;
  int error_code;
};

std::expected<std::string, execute_program_error> execute_program(const std::string& path, const exec_environment& env) {

  int es_ejecutable = access(path.c_str(), X_OK);
  if (es_ejecutable < 0) {
    return std::unexpected(execute_program_error(127, errno));
  }

  char* args[] = { nullptr };
  const size_t tam_buffer {256};
  int pipefd[2];
  int result_pipe = pipe(pipefd);
  if (result_pipe < 0) {
    return std::unexpected(execute_program_error(127, errno));
  }
  pid_t pid = fork();

  if (pid == 0) {
    // Proceso hijo
    close(pipefd[0]);
    int dup2_result = dup2(pipefd[1], 1);
    if (dup2_result < 0) {
      int error = errno;
      close(pipefd[1]);
      return std::unexpected(execute_program_error(127, error));
    }
    // variables de entorno
    std::string request_path = "REQUEST_PATH=" + env.get_path();
    std::string server_basedir = "SERVER_BASEDIR=" + env.get_base_dir();
    std::string remote_port = "REMOTE_PORT=" + env.get_port();
    std::string remote_ip = "REMOTE_IP=" + env.get_ip();

    const char* var_entorno[] = {request_path.c_str(), server_basedir.c_str(),remote_port.c_str(),
                                 remote_ip.c_str(), nullptr};
    // exec
    execve(path.c_str(), args, const_cast<char* const*>(var_entorno));
    // fallo en exec
    close(pipefd[1]);
    _exit(EXIT_FAILURE);
  }
  else if (pid > 0) {
    // Proceso padre
    int status {};
    close(pipefd[1]);
    int waitpid_result = waitpid(pid, &status, 0);
    if (waitpid_result == -1) {
      int error = errno;
      close(pipefd[1]);
      return std::unexpected(execute_program_error(127, error));
    }
    else if (WIFEXITED(status)) {
      // Terminación normal del proceso hijo
      if (WEXITSTATUS(status) == EXIT_SUCCESS) {
        // Terminación sin errores del proceso hijo
        std::array<char, tam_buffer> buffer {};
        bool flag {true};
        std::string listen {};
        while (flag) {
          ssize_t nbytes = read(pipefd[0], buffer.data(), tam_buffer);
          if (nbytes < 0) {
            int error = errno;
            close(pipefd[0]);
            return std::unexpected(execute_program_error(127, error));
          }
          else {
            listen.append(buffer.data(), 0, static_cast<size_t>(nbytes));
              if (nbytes < static_cast<ssize_t>(tam_buffer)) {
                flag = false; // Datos agotados
              }
          }
        }
        close(pipefd[0]);
        return listen; 
        }
        else {
          // Terminación con errores del proceso hijo
          close(pipefd[0]);
          std::cerr << "Proceso hijo termina con errores\n";
          std::unexpected(execute_program_error(WEXITSTATUS(status), 0));
        }
      }
      else {
      // Terminación forzada del proceso hijo
      std::cerr << "Terminación anormal del proceso hijo\n";
      return std::unexpected(execute_program_error(EXIT_SUCCESS, EXIT_SUCCESS));
      }
  }

  else {
    // Error en fork()
    int error = errno;
    close(pipefd[0]);
    close(pipefd[1]);
    return std::unexpected(execute_program_error(127, error));
  }
  return std::unexpected(execute_program_error{127, -1});
}

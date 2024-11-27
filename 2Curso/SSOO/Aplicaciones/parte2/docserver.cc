#include <iostream>
#include <fstream>
#include <string>
#include <format>

#include "funciones.h"


int main(int argc, char* argv[]) {
  auto options = parse_args(argc, argv);
  if (! options.has_value()) {
    // Usar options.error() para comprobar el motivo del error...
    if (options.error() == parse_args_errors::missing_argument) {
      // Mostrar mensaje de error por falta de argumento...
      std::cerr << argv[0] << ": Error en los argumentos" << std::endl;
      std::cerr << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    }
    else if (options.error() == parse_args_errors::unknown_option) {
      // Mostrar mensaje de error por opción desconocida...
      std::cerr << argv[0] << ": Error desconocido" << std::endl;
      std::cerr << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    }
    // ...
    return EXIT_FAILURE;
  }
  // Usar options.value() para acceder a las opciones...
  if (options.value().show_help) {
    std::cout << "Uso: " << argv[0] << " <opciones> <archivo>" << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -h, --help            Muestra esta ayuda" << std::endl;
    std::cout << "  -v, --verbose         Muestra información detallada" << std::endl;
    std::cout << "  -p, --puerto <PUERTO> -" << std::endl;
    return EXIT_SUCCESS;
  }
  // ...
  
  if(options.value().verbose) {
    std::cerr << "make_socket: se crea el socket con puerto \"" << options.value().puerto << "\"" << std::endl;
  }
  auto socket_fd = make_socket(options.value().puerto);
  if (! socket_fd.has_value()) {
    std::cerr << argv[0] << ": Error en la creación del socket" << std::endl;
    return EXIT_FAILURE;
  }
  
  if(options.value().verbose) {
    std::cerr << "listen_connection: se pone el socket con puerto \"" << options.value().puerto << "\" a la escucha" << std::endl;
  }
  int escucha = listen_connection(socket_fd.value());
  if(escucha != ESUCCESS) {
    std::cerr << argv[0] << ": Error al poner el socket a la escucha" << std::endl;
    return EXIT_FAILURE;
  }
  
  while(true) {
    sockaddr_in client_addr{};
    auto socket2 = accept_connection(socket_fd.value(), client_addr);
    if (!socket2.has_value()) {
        std::cerr << argv[0] << ": Error al aceptar una conexión" << std::endl;
        return EXIT_FAILURE;
    }

    if (options.value().verbose) {
        std::cerr << "accept: conexión aceptada" << std::endl; // Puerto en formato host
    }

    if(options.value().verbose) {
    std::cerr << "open: se abre el archivo \"" << options.value().output_filename << "\"" << std::endl;
    }
    auto fd = read_all(options.value().output_filename);
    if (! fd.has_value()) {
      if (errno == ENOENT) {
        std::cerr << argv[0] << ": Error el archivo no existe" << std::endl;
        std::string header = "404 Not Found";
        send_response(socket2.value(), header, "");
      } else {
        std::cerr << argv[0] << ": Error no se pudo abrir el archivo" << std::endl;
        std::string header = "403 Forbidden";
        send_response(socket2.value(), header, "");
      }
    } 
    else {
      if(options.value().verbose) {
        std::cerr << "read: se leen " << fd.value().get_size() << " bytes del archivo \"" << options.value().output_filename << "\"" << std::endl;
      }
      std::string header = std::format("Content-Length: {}\n", fd.value().get_size());

      if(options.value().verbose) {
        std::cerr << "send: se envía el contenido del archivo" << std::endl;
      }
      int mensaje = send_response(socket2.value(), header, fd.value().get());
      if (mensaje != ESUCCESS) {
        std::cerr << argv[0] << ": Error al enviar el mensaje" << std::endl;
      }
    }

    if(options.value().verbose) {
    std::cerr << "close: se cierra la conexión " << std::endl;
    }
  }

  return EXIT_SUCCESS;
}

#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <sys/types.h> // waitpid
#include <sys/wait.h>  // waitpid
#include <array>
#include <arpa/inet.h> // modificación

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
    std::cout << "Uso: " << argv[0] << " <opciones>" << std::endl;
    std::cout << "Opciones:" << std::endl;
    std::cout << "  -h, --help            Muestra esta ayuda" << std::endl;
    std::cout << "  -v, --verbose         Muestra información detallada" << std::endl;
    std::cout << "  -p, --puerto <PUERTO>" << std::endl;
    std::cout << "  -b, --base <RUTA>" << std::endl;
    std::cout << "  -e, --echo            Envía al cliente su dirección ip y su puerto" << std::endl;
    return EXIT_SUCCESS;
  }
  // ...
  size_t max_size = 4096;

  // Variables de entorno

  if (!options.value().b_puerto) {
    const char* puerto_str = getenv("DOCSERVER_PORT");
    uint16_t puerto = 8080;
    if (puerto_str != nullptr && *puerto_str != '\0') {
      puerto = static_cast<uint16_t>(std::stoi(puerto_str));
    }
    options.value().puerto = puerto;
  } 

  if (!options.value().b_ruta) {
    const char* ruta_str = getenv("DOCSERVER_BASEDIR");
    if(ruta_str == nullptr || *ruta_str == '\0') {
      char* ruta_cwd = getcwd(nullptr, 4096);
      ruta_str = ruta_cwd;
    }
    options.value().ruta = ruta_str;
  }
  

  // Creación del socket
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

  // Poner el socket en modo escucha
  int escucha = listen_connection(socket_fd.value());
  if(escucha != ESUCCESS) {
    std::cerr << argv[0] << ": Error al poner el socket a la escucha" << std::endl;
    return EXIT_FAILURE;
  }
  

  // Bucle infinito
  while(true) {
    sockaddr_in client_addr{};
    auto socket2 = accept_connection(socket_fd.value(), client_addr);
    if (!socket2.has_value()) {
        std::cerr << argv[0] << ": Error al aceptar una conexión" << std::endl;
        return EXIT_FAILURE;
    }

    if (options.value().verbose) {
        std::cerr << "accept: conexión aceptada" << std::endl; 
    }
    /*
    // Modificación
    if (options.value().b_echo) {
      char* ip = inet_ntoa(client_addr.sin_addr);
      std::string ip_str (ip);
      uint16_t puerto_echo = ntohs(client_addr.sin_port);
      std::string puerto_echo_str = std::to_string(puerto_echo);
      std::string header = "He aceptado tu conexión desde la IP " + ip_str + " y puerto " + puerto_echo_str;
      send_response(socket2.value(), header, "");
    }
    else {*/
    if (options.value().verbose) {
        std::cerr << "receive_request: se recibirá la petición del cliente" << std::endl; 
    }
    auto request = receive_request(socket2.value(), max_size);
    if (!request.has_value()) {
      std::cerr << argv[0] << ": Error al leer la petición del cliente" << std::endl;
    }
    else {
      // procesar petición
      std::istringstream iss(request.value());
      std::string get_str, ruta_str;
      iss >> get_str >> ruta_str;

      if (get_str != "GET" || ruta_str[0] != '/') {
        std::string header = "400 Bad Request";
        send_response(socket2.value(), header, "");
      } 
      else {
        std::string subcadena = ruta_str.substr(0, 5);
        ruta_str = options.value().ruta + ruta_str;
        if (subcadena == "/bin/") {
          
          // ejecución de programa
          if (options.value().verbose) {
            std::cerr << "exec: se ejecutará el programa: " << ruta_str << std::endl;
          }
          // variables de entorno
          exec_environment env {ruta_str, options.value().ruta, client_addr.sin_port, client_addr.sin_addr.s_addr};

          if (options.value().verbose) {
            std::cerr << "exec: se ejecutará el programa: " << ruta_str << std::endl;
          }
          auto salida = execute_program(ruta_str, env);
          if (salida.has_value()) {
            if(options.value().verbose) {
              std::cerr << "send: se envía la salida del programa" << std::endl;
            }
            int mensaje = send_response(socket2.value(), salida.value(), "");
            if (mensaje != ESUCCESS) {
              std::cerr << argv[0] << ": Error al enviar el mensaje" << std::endl;
            }
          } else {
              if (salida.error().error_code == ENOENT) {
                std::cerr << argv[0] << ": Error el programa no existe" << std::endl;
                std::string header = "404 Not Found";
                send_response(socket2.value(), header, "");
              } else if (salida.error().error_code == EACCES) {
                std::cerr << argv[0] << ": Error no se pudo ejecutar el programa" << std::endl;
                std::string header = "403 Forbidden";
                send_response(socket2.value(), header, "");
              } else {
                std::cerr << argv[0] << ": Error en la ejecución del programa" << std::endl;
                std::string header = "500 Internal Server Error";
                send_response(socket2.value(), header, "");
              }
          }
        }
        else {
          // lectura de un archivo
          if(options.value().verbose) {
            std::cerr << "open: se abre el archivo \"" << ruta_str << "\"" << std::endl;
          }
          auto fd = read_all(ruta_str);
          if (! fd.has_value()) {
            if (fd.error() == ENOENT) {
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
              std::cerr << "read: se leen " << fd.value().get_size() << " bytes del archivo \"" << ruta_str << "\"" << std::endl;
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
        } 
      }
    }

    if(options.value().verbose) {
    std::cerr << "close: se cierra la conexión " << std::endl;
    }
  }
  //}

  return EXIT_SUCCESS;
}

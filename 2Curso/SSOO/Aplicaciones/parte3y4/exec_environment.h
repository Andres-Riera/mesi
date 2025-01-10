#pragma once

#include <sys/socket.h> 
#include <netinet/ip.h>
#include <sys/un.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <cstdlib>
#include <sstream>

/*
El programa docserver configurará una serie de variables de entorno con información para
que el programa que se ejecute pueda saber más sobre la petición que se le ha hecho y el
entorno en el que se está ejecutando:
• REQUEST_PATH: La ruta del archivo que el cliente indicó en la petición, que será la ruta
del programa que se está ejecutando.
• SERVER_BASEDIR: La del directorio base que está usando docserver.
• REMOTE_PORT: El puerto desde el que se ha hecho la petición.
• REMOTE_IP: La dirección IP del cliente que ha hecho la petición.

*/

class exec_environment {
 public:
  exec_environment(std::string path, std::string base_dir, uint16_t port, uint32_t ip)
      : path_(path), base_dir_(base_dir) {
    port_ = std::to_string(port);
    ip_ = std::to_string(ip);
    setenv("REQUEST_PATH", path_.c_str(), 1);
    setenv("SERVER_BASEDIR", base_dir_.c_str(), 1);
    setenv("REMOTE_PORT", port_.c_str(), 1);
    setenv("REMOTE_IP", ip_.c_str(), 1);
  }
  std::string get_path() const { return path_; }
  std::string get_base_dir() const { return base_dir_; }
  std::string get_port() const { return port_; }
  std::string get_ip() const { return ip_; }

 private:
  std::string path_;
  std::string base_dir_;
  std::string port_;
  std::string ip_;
};
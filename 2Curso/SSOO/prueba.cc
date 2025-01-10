#include <unistd.h>    // pipe
#include <string>
#include <iostream>
#include <sys/types.h> // waitpid
#include <sys/wait.h>  // waitpid
#include <array>


int main() {
   const size_t tam_buffer {256};
   int pipefd[2];
   int result_pipe = pipe(pipefd);
   if (result_pipe < 0) {
       return errno;
   }
   pid_t pid = fork();
   if (pid == 0) {
       // Proceso hijo
       close(pipefd[0]);
       int dup2_result = dup2(pipefd[1], 1);
       if (dup2_result < 0) {
           int error = errno;
           close(pipefd[1]);
           return error;
       }
       std::string say {"Hola, mundo!"};
       // std::cout << say;
       ssize_t nbytes = write(1, say.data(), say.size());
       if (nbytes < 0 ) {
           int error = errno;
           close(pipefd[1]);
           return error;
       }
       else {
           close(pipefd[1]);
           return EXIT_SUCCESS;
       }
   }
   else if (pid > 0) {
       // Proceso padre
       int status {};
       close(pipefd[1]);
       int waitpid_result = waitpid(pid, &status, 0);
       if (waitpid_result == -1) {
           int error = errno;
           close(pipefd[1]);
           return error;
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
                       int error  = errno;
                       close(pipefd[0]);
                       return error;
                   }
                   else {
                       listen.append(buffer.data(), 0, static_cast<size_t>(nbytes));
                       if (nbytes < tam_buffer) {
                           flag = false; // Datos agotados
                       }
                   }
               }
               close(pipefd[0]);
               std::cout << "Proceso padre escucha:\n" << listen << std::endl;
               return EXIT_SUCCESS;
               
           }
           else {
               // Terminación con errores del proceso hijo
               close(pipefd[0]);
               std::cerr << "Proceso hijo termina con errores\n";
               return WEXITSTATUS(status);
           }
       }
       else {
           // Terminación forzada del proceso hijo
           std::cerr << "Terminación anormal del proceso hijo\n";
           return EXIT_SUCCESS;
       }
   }
   else {
       // Error en fork()
       int error = errno;
       close(pipefd[0]);
       close(pipefd[1]);
       return error;
   }




   return EXIT_SUCCESS;
}

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream> // Sustituir <print> por <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = getpid();

    // Crear un proceso hijo
    pid_t child = fork();

    if (child == 0)
    {                   
        // Aquí solo entra el proceso hijo
        std::cout << "[HIJO] ¡Soy el proceso hijo!" << std::endl;
        std::cout << "[HIJO] El valor de mi variable 'child' es: " << child << std::endl;
        std::cout << "[HIJO] Este es mi PID: " << getpid() << std::endl;
        std::cout << "[HIJO] El valor de mi variable 'pid' es: " << pid << std::endl;
        std::cout << "[HIJO] El PID de mi padre es: " << getppid() << std::endl;
        
        std::cout << "[HIJO] Durmiendo 10 segundos..." << std::endl;
        sleep(10);

        int status = 42;
        std::cout << "[HIJO] Salgo con " << status << " ¡Adiós!" << std::endl;
        return status;
    }
    else if (child > 0)
    {   
        // Aquí solo entra el proceso padre
        std::cout << "[PADRE] ¡Soy el proceso padre!" << std::endl;
        std::cout << "[PADRE] El valor de mi variable 'child' es: " << child << std::endl;
        std::cout << "[PADRE] Este es mi PID: " << getpid() << std::endl;
        std::cout << "[PADRE] El valor de mi variable 'pid' es: " << pid << std::endl;
        std::cout << "[PADRE] El PID de mi padre es: " << getppid() << std::endl;

        std::cout << "[PADRE] Voy a esperar a que mi hijo termine..." << std::endl;
        
        int status;
        wait(&status);
        std::cout << "[PADRE] El valor de salida de mi hijo fue: " << WEXITSTATUS(status) << std::endl;
        
        std::cout << "[PADRE] ¡Adiós!" << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        // Aquí solo entra el padre si no pudo crear el hijo
        std::cerr << "Error (" << errno << ") al crear el proceso: " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
}

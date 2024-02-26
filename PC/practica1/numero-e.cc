#include <iostream>

int main() {
    std::cout << "PR1: Principio de computadores.\n";
    std::cout << "\n";
    double error;
    std::cout << "Introduzca el máximo error permitido: ";
    std::cin >> error;
    std::cout << "\n";
    while (error < 0.00001 || error >= 1) {
            std::cout << "Error: el dato introducido debe cumplir 0,00001 <= dato < 1\n";
            std::cout << "\n";
            std::cout << "Introduzca el máximo error permitido: ";
            std::cin >> error;
            std::cout << "\n";
    }
    double e{1.0};
    double f{1.0};
    double ultimo{1.0};
    double terminos{1.0};
    while (ultimo > error) {
        f = f * (terminos);
        ultimo = 1.0 / f;
        e += ultimo;
        terminos += 1.0;
    }
    std::cout << "Numero e: " << e << "\n";
    std::cout << "Numero de terminos: " << terminos << "\n";
    std::cout << "PR1: Fin del programa.\n";
    return 0;
}
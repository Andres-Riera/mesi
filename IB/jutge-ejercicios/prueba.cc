#include <iostream>
#include <vector>

int main() {
    std::vector<int> numeros; // Declara un vector para almacenar los números enteros
    int numero;
    while (std::cin >> numero) {
        numeros.push_back(numero); // Agrega el número al vector
    }

    // Imprime los números almacenados en el vector
    std::cout << "Números ingresados:" << std::endl;
    for (int i = 0; i < numeros.size(); i++) {
        std::cout << numeros[i] << " ";
    }

    return 0;
}

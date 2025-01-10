#include <iostream>

int main() {
    int decimal;
    std::cin >> decimal;
    int binary {0};
    int j = 1;
    while (decimal >= 1) {
        binary = binary + decimal % 2 * j;
        decimal /= 2;
        j *= 10;
    }
    std::cout << binary;
    
    return 0;
}

#include <iostream>

int main() {
    int cycle;
    std::cin >> cycle;
    int value;
    int past {1000000};
    int sum {0};
    for (int i = 0; i < cycle; i ++) {
        while (std::cin >> value) {
            if (value > past && past != 0) {
                sum = sum +1;
            }
            past = value;
        }
        std::cout << sum << std::endl;
        sum = 0;
    }

    return 0;
}

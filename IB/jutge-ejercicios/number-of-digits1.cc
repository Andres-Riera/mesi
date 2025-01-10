#include <iostream>
#include <string>

int main() {
    std::string number;
    std::cin >> number;
    int count {0};
    for (int i = 0; i < number.size(); i++) {
        count += 1;
    }
    std::cout << "The number of digits of " << number << " is " << count 
              << "." << std::endl;
    return 0;
}

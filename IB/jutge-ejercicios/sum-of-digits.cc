#include <iostream>
#include <vector>

int main() {
    int number;
    while(std::cin >> number) {
        int copy = number;
        std::vector<int> sum;
        while (number >= 1) {
            int digit = number % 10;
            number /= 10;
            sum.push_back(digit);
        }
        int result {0};
        for (int i = 0; i < sum.size(); i++) {
            result += sum[i];
        }
        std::cout << "The sum of the digits of " << copy << " is " << result << "." << std::endl;
    }
    
    return 0;
}

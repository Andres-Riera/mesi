#include <iostream>
#include <vector>

int main() {
    int number;
    std::cin >> number;
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
    std::cout << result << std::endl;
    
    return 0;
}

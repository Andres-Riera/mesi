#include <iostream>
#include <vector>

int Result(std::vector<int> numbers, int value) {
    int result {0};
    for (int i = 0; i < numbers.size() - 1; i++) {
        result = result * value + numbers[i];
    }
    return result;
}

int main() {
    std::vector<int> numbers;
    int number;
    while (std::cin >> number) {
        numbers.push_back(number);
    }
    int value = numbers.back();
    std::cout << Result(numbers, value) << std::endl;
    return 0;
}

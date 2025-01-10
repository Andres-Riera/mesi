#include <iostream>
#include <vector>

bool Past(std::vector<int> past, int number) {
  for (int k = 0; k < past.size(); k++) {
    if (number == past[k]) {
      return false;
    }
  }
  return true;
}

int main() {
  int times;
  std::cin >> times;
  std::vector<int> numbers;
  for (int i = 0; i < times; i++) {
    int value;
    std::cin >> value;
    numbers.push_back(value);
  }
  std::vector<int> past;
  for (int i = 0; i < numbers.size(); i++) {
    int number = numbers[i];
    int count {0};
    if (Past(past, number)) {
      for (int j = 0; j < numbers.size(); j++) {
        if (number == numbers[j]) {
          count++;
        }
      }
      past.push_back(number);
      std::cout << number << " : " << count << std::endl;
    }
  }
  return 0;
}

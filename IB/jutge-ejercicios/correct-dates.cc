#include <iostream>

int main() {
  int day;
  int month;
  int year;
  while(std::cin >> day >> month >> year) {
    if (day > 31 || day < 1 || month < 1 || month > 12 || year < 1800) {
      std::cout << "Incorrect Date" << std::endl;
    }
    else if (month <= 7 && month != 2) {
      if (month % 2 == 0 && day <= 30) {
        std::cout << "Correct Date" << std::endl;
      }
      else if (month % 2 != 0) {
        if (day > 31) {
          std::cout << "Incorrect Date" << std::endl;
        }
        else {
          std::cout << "Correct Date" << std::endl;
        }
      }
      else {
        std::cout << "Incorrect Date" << std::endl;
      }
    }
    else if (month > 7) {
      if (month % 2 == 0 && day <= 31) {
        std::cout << "Correct Date" << std::endl;
      }
      else if (month % 2 != 0) {
        if (day > 30) {
          std::cout << "Incorrect Date" << std::endl;
        }
        else {
          std::cout << "Correct Date" << std::endl;
        }
      }
    }
    else if (month == 2 && year % 4 == 0 && day <= 29) {
      if (year % 400 == 0) {
        std::cout << "Correct Date" << std::endl;
      }
      else if (year % 100 == 0 && day == 29) {
        std::cout << "Incorrect Date" << std::endl;
      }
      else {
        std::cout << "Correct Date" << std::endl;
      }
    }
    else {
      if (day > 28) {
        std::cout << "Incorrect Date" << std::endl;
      }
      else {
        std::cout << "Correct Date" << std::endl;
      }
    }
  }

  return 0;
}

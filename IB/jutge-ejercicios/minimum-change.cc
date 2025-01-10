#include <iostream>

int main () {
  int euros;
  int cents;
  std::cin >> euros >> cents;
  int count {0};
  while (euros >= 500) {
    euros -= 500;
    count++;
  }
  std::cout << "Banknotes of 500 euros: " << count << std::endl;
  count = 0;
  while (euros >= 200) {
    euros -= 200;
    count++;
  }
  std::cout << "Banknotes of 200 euros: " << count << std::endl;
  count = 0;
  while (euros >= 100) {
    euros -= 100;
    count++;
  }
  std::cout << "Banknotes of 100 euros: " << count << std::endl;
  count = 0;
  while (euros >= 50) {
    euros -= 50;
    count++;
  }
  std::cout << "Banknotes of 50 euros: " << count << std::endl;
  count = 0;
  while (euros >= 20) {
    euros -= 20;
    count++;
  }
  std::cout << "Banknotes of 20 euros: " << count << std::endl;
  count = 0;
  while (euros >= 10) {
    euros -= 10;
    count++;
  }
  std::cout << "Banknotes of 10 euros: " << count << std::endl;
  count = 0;
  while (euros >= 5) {
    euros -= 5;
    count++;
  }
  std::cout << "Banknotes of 5 euros: " << count << std::endl;
  count = 0;
  while (euros >= 2) {
    euros -= 2;
    count++;
  }
  std::cout << "Coins of 2 euros: " << count << std::endl;
  count = 0;
  while (euros >= 1) {
    euros -= 1;
    count++;
  }
  std::cout << "Coins of 1 euro: " << count << std::endl;
  
  count = 0;
  while (cents >= 50) {
    cents -= 50;
    count++;
  }
  std::cout << "Coins of 50 cents: " << count << std::endl;
  count = 0;
  while (cents >= 20) {
    cents -= 20;
    count++;
  }
  std::cout << "Coins of 20 cents: " << count << std::endl;
  count = 0;
  while (cents >= 10) {
    cents -= 10;
    count++;
  }
  std::cout << "Coins of 10 cents: " << count << std::endl;
  count = 0;
  while (cents >= 5) {
    cents -= 5;
    count++;
  }
  std::cout << "Coins of 5 cents: " << count << std::endl;
  count = 0;
  while (cents >= 2) {
    cents -= 2;
    count++;
  }
  std::cout << "Coins of 2 cents: " << count << std::endl;
  count = 0;
  while (cents >= 1) {
    cents -= 1;
    count++;
  }
  std::cout << "Coins of 1 cent: " << count << std::endl;
  
  return 0;
}

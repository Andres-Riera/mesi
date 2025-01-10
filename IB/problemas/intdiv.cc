#include <iostream>

int main(){
  int number1 {0};
  int number2 {0};
  std::cin >> number1 >> number2;
  int number3 {number1 / number2};
  int number4 {number1 % number2};
  if (number1>0){
    std::cout << number3 << " " << number4 << std::endl;
  }
  else {
    if (number4<0) {
        number3 = number3-1;
        int number5 = number3*number2;
        number4 = number1 - number5;
      std::cout << number3 << " " << number4 << std::endl;
    }
    else {
      std::cout << number3 << " " << number4 << std::endl;  
    }
  }
  return 0;
}

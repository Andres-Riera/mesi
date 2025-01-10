#include <iostream>
#include <cmath>

int max4(int number, int number2, int number3, int number4) {
  if (number >= number2 && number >= number3 && number >= number4) {
    return number;
  } else if (number2 >= number3 && number2 >= number4) {
    return number2;
  } else if(number3 >= number4) {
    return number3;
  } else {
    return number4;
  }
}

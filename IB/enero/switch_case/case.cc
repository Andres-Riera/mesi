#include "case.h"

void Switch(std::string& palabra) {
  for(int i = 0; i < static_cast<int>(palabra.size()); i++) {
    if(palabra[i] >= 'A' && palabra[i]<= 'Z') {
      palabra[i] += 32;
    } else if(palabra[i] >= 'a' && palabra[i]<= 'z') {
      palabra[i] -= 32;
    }
  }
}
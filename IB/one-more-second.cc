#include <iostream>

void Hora(int& h) { // Si las horas son mayores de 24, pasará un día hasta que
		    // sean menores a 24
  while (h >= 24) {
  h = h - 24;
  }
}

void Minuto(int& m) { // Lo mismo que las horas pero con minutos
  while (m >= 60) {
  m = m - 60;
  }
}

void Segundo(int& s) { // Lo mismo que lo anterior pero con segundos
  while (s >= 60) {
  s = s - 60;
  }
}

void Hora_mas_uno (int& h, int& m, int s) { //Ajusta la hora con el segundo
					    //extra
  while (s >= 60) {
    m = m + 1;
    s = s - 60;
  }
  int temp = m;
  while (temp >= 60) {
    h = h + 1;
    temp = temp - 60;
  }
}

void Reloj(int h, int m, int s) { //Imprime la hora que marca el reloj
  if (h < 10) {
    std::cout << "0" << h << ":";
  }
  else {
    std::cout << h << ":";
  }
  if (m < 10) {
    std::cout << "0" << m << ":";
  }
  else {
    std::cout << m << ":";
  }
  if (s < 10) {
    std::cout << "0" << s << std::endl;
  }
  else {
    std::cout << s << std::endl;
  }
}

int main() {
  int horas;
  int minutos;
  int segundos;
  std::cin >> horas >> minutos >> segundos;
  segundos = segundos + 1;
  Hora_mas_uno(horas, minutos, segundos);
  Hora(horas);
  Minuto(minutos);
  Segundo(segundos);
  Reloj(horas, minutos, segundos);
  
  return 0;
}

#include <iostream>
#include <cmath>

using namespace std;
int main() {
  int n = 10;
  int A[n] = {5, 3, 2, 1, 5, 1, 4, 2, 1, 6}; 
  int* multiplos = new int[n];
  int* no_multiplos = new int[n];
  int multiplos_de_tres = 0;
  int no_multiplo_de_tres = 0;

  for (int i = 0; i < n; i++) {
    if (A[i] % 3 == 0) {
      multiplos[multiplos_de_tres] = i;
      multiplos_de_tres++;
    } else {
      no_multiplos[no_multiplo_de_tres] = A[i];
      no_multiplo_de_tres++;
    }
  }

  cout << "Multiplos de 3: " << multiplos_de_tres << endl;

  int suma = 0;
  for (int i = 0; i < multiplos_de_tres; i++) {
    cout << multiplos[i] << " ";
    suma += multiplos[i];
  }
  if (suma % 2 == 0) {
    cout << "\nsuma: " << suma << " es par\n";
  } else {
    cout << "\nsuma: " << suma << " es impar\n";
  }
  
  suma = 0;
  for (int i = 0; i < no_multiplo_de_tres; i++) {
    cout << no_multiplos[i] << " ";
    suma += no_multiplos[i];
  }
  if (suma % 2 == 0) {
    cout << "\nsuma: " << suma << " es par\n";
  } else {
    cout << "\nsuma: " << suma << " es impar\n";
  }

  int suma_modulo = 0;
  for (int i = 0; i < no_multiplo_de_tres; i++) {
    suma_modulo += no_multiplos[i] * no_multiplos[i];
  }
  cout << "Modulo no multiplos = " << sqrt(suma_modulo) << endl;
  return 0;
}
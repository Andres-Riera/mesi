/* 
1. Pedir entero al usuario (n)
2. Si n es 0 termina el programa
3. Probar desde 2 hasta n-1 si es divisible
4. Si se encontró un divisible mostrarlo en pantalla
5. Caso contrario decir que es primo
6. Volver al punto 1 
*/

#include <iostream>

using namespace std;
int main() {
    
    cout << "Números primos\n";

    int n;
    do {
        cout << "Introduzca un número entero (0 si quiere finalizar la ejecución): ";
        cin >> n;
        int primo = 1;
        if (n == 0) { break; }
        
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                cout << n << " no es primo, su divisor más pequeño es " << i << "\n";
                primo = 0;
                break;
            }
        }

        if (primo == 1) {
            cout << n << " es un número primo\n";
        }
    } while (n != 0);

    cout << "Fin de ejecución\n"

    return 0;
 }

 /* 
 Asignación de variables a registros
 n -> $s0
 primo -> $s2
 i -> $s1

    .data
str_titulo:     .asciiz "Numeros primos\n"
str_introduzca  .asciiz "\nIntroduzca un numero"
str_divisible   .asciiz "El número es divisible por "
str_salto       .asciiz "\n"
str_esprimo     .asciiz "Es primo\n"
str_termina     .asciiz "Fin de ejecución\n"

    .text
int main() {
main:
    
    # cout << "Números primos\n";
    li $v0,4
    la $a0,str_titulo
    syscall

    int n;
    do {
        cout << "Introduzca un número entero (0 si quiere finalizar la ejecución): ";
        cin >> n;
        int primo = 1;
        if (n == 0) { break; }
        
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                cout << n << " no es primo, su divisor más pequeño es " << i << "\n";
                primo = 0;
                break;
            }
        }

        if (primo == 1) {
            cout << n << " es un número primo\n";
        }
    } while (n != 0);

    cout << "Fin de ejecución\n"

    return 0;
 }

                li $v0,10
                syscall
 */
.data
str_titulo:     .asciiz "Numeros primos\n"
str_introduzca: .asciiz "Introduzca un numero"
str_divisible:  .asciiz "El número es divisible por "
str_salto:      .asciiz "\n"
str_esprimo:    .asciiz "Es primo\n"
str_termina:    .asciiz "Fin de ejecución\n"

    .text
#int main() {
main:
    li $v0, 4
    li $a0, str_titulo
 #   int n;
  #  do {
do:
   #     cout << "Introduzca un número entero (0 si quiere finalizar la ejecución): ";
    li $v0, 4
    li $a0, str_introduzca
    syscall 
    #    cin >> n;
    li $v0, 5
    syscall
    move $s0, $v0
     #   int primo = 1;
    li $t0, 1
    move $s1, $t0
      #  if (n == 0) { break; }
    beq $s0, 0, do_fin
    
    li $t0, 2
    move $s2, $t0
       #
for:
    blt $s2, $s0, for_dentro
    b for_fin
        #for (int i = 2; i < n; i++) {

for_dentro:
        #    if (n % i == 0) {
         #       cout << n << " no es primo, su divisor más pequeño es " << i << "\n";
          #      primo = 0;
           #     break;
            #}
        #}

        #if (primo == 1) {
         #   cout << n << " es un número primo\n";
        #}
while:
    #} while (n != 0);
    bne $s0, 0, do
    
do_fin:
    #cout << "Fin de ejecución\n"

    #return 0;
 #}
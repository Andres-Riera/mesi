#// Programa para evaluar polinomio tercer grado

	.data
str_titulo: .asciiz "\nEvaluacion polinomio f(x) = a x^3  + b x^2 + c x + d  en un intervalo [r,s]\n"
str_introduzca: .asciiz "\nIntroduzca los valores de a,b,c y d (separados por retorno de carro):\n"
str_introduzca2: .asciiz "Introduzca [r,s] (r y s enteros, r <= s)  (separados por retorno de carro):\n"
str_fx: .asciiz "\nf("
str_fx2: .asciiz ") = "
str_fin: .asciiz "\n\nTermina el programa\n"

	.text

main:
#  std::cout << "\nEvaluacion polinomio f(x) = a x^3  + b x^2 + c x + d  en un intervalo [r,s]\n";
  li $v0, 4
  li $a0, str_titulo
  syscall
#  std::cout << "\nIntroduzca los valores de a,b,c y d (separados por retorno de carro):\n";
  li $v0, 4
  li $a0, str_introduzca
  syscall
#  std::cin >> a;
  li $v0, 6
  syscall
  mov.s $f20, $f0
#  std::cin >> b;
  li $v0, 6
  syscall
  mov.s $f21, $f0
#  std::cin >> c;
  li $v0, 6
  syscall
  mov.s $f22, $f0
#  std::cin >> d;
  li $v0, 6
  syscall
  mov.s $f23, $f0
#  int r,s;
do:
#  do {
#    std::cout << "Introduzca [r,s] (r y s enteros, r <= s)  (separados por retorno de carro):\n";
  li $v0, 4
  li $a0, str_introduzca2
  syscall
#    std::cin >> r;
  li $v0, 5
  syscall
  move $s0, $v0
#    std::cin >> s;
  li $v0, 5
  syscall
  move $s1, $v0
#  } while (r > s);
while_condicion:
  bgt $s0, $s1, do

do_fin:
  li $t0,$s0 # $t0 = r
  mtc1 $t0,$f2 # $f2 = r
  cvt.s.w $f24,$f2 # $f24 = r (float)

for:
#  for (int x = r ; x <= s ; x++) {
  ble $s0,$s1,for_dentro
  b for_fin
for_dentro: 
#    float f = a*x*x*x + b*x*x + c*x + d;
  mul.s $f4,$f20,$f24
  mul.s $f4,$f4,$f24
  mul.s $f4,$f4,$f24

  mul.s $f5,$f21,$f24
  mul.s $f5,$f5,$f24

  mul.s $f6,$f22,$f24

  add.s $f4,$f4,$f5
  add.s $f4,$f4,$f6
  add.s $f25,$f4,$f23

#    if (f >= 2.1) {
  blt $f4,2.1,for_incremento

#      std::cout << "\nf(" << x << ") = " << f;
  li $v0, 4
  li $a0, str_fx
  syscall

  li $v0, 1
  li $a0, $s0
  syscall

  li $v0, 4
  li $a0, str_fx2
  syscall

  li $v0, 5
  li $f12,$f28
  syscall

for_incremento: 
  addi $s0, $s0, 1
  li.s $f0, 1.0
  add.s $f24, $f0

for_fin:
#  std::cout << "\n\nTermina el programa\n";
  li $v0, 4
  li $a0, str_fin
  syscall

  li $v0, 10
  syscall

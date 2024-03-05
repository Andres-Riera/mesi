# Programa para evaluar polinomio tercer grado

	.data
titulo:		.asciiz "\nEvaluacion polinomio f(x) = a x^3  + b x^2 + c x + d  en un intervalo [r,s]\n"
valores:	.asciiz "\nIntroduzca los valores de a,b,c y d (separados por retorno de carro):\n"
rys:		.asciiz "Introduzca [r,s] (r y s enteros, r <= s)  (separados por retorno de carro):\n"
funcion1:	.asciiz "\nf("
funcion2:	.asciiz ") = "
fin:		.asciiz "\n\nTermina el programa\n"
limite: .float 2.1
uno:		.float 1.0

	.text
	
main:
	# Se muestra el título
	li 			$v0, 4
	la 			$a0, titulo
	syscall
	# Se muestra la cadena que pide los valores a, b, c y d
	li 			$v0, 4
	la 			$a0, valores
	syscall
	# Se espera la entrada del valor a en punto flotante
	li 			$v0, 6
	syscall
	mov.s 	$f20, $f0
	# Se espera la entrada del valor b en punto flotante
	li 			$v0, 6
	syscall
	mov.s 	$f21, $f0
	# Se espera la entrada del valor c en punto flotante
	li 			$v0, 6
	syscall
	mov.s 	$f22, $f0
	# Se espera la entrada del valor d en punto flotante
	li 			$v0, 6
	syscall
	mov.s 	$f23, $f0
	
	
do:
	# Se muestra la cadena que pide los valores de r y s
	li 			$v0, 4
	la 			$a0, rys
	syscall
	# Se espera la entrada del valor entero de r
	li 			$v0, 5
	syscall
	move 		$s0, $v0
	# Se espera la entrada del valor entero de s
	li 			$v0, 5
	syscall
	move 		$s1, $v0


while:
	# while (r > s);
	bgt 		$s0, $s1, do


for:
#  for (int x = r ; x <= s ; x++) {
	ble 		$s0, $s1, for_dentro
	b				for_fin
for_dentro:	
#    float f = a*x*x*x + b*x*x + c*x + d;
	mtc1 		$s0, $f4
	cvt.s.w $f4, $f4 # convertir x a flotante
	mtc1 		$s1, $f5
	cvt.s.w	$f5, $f5 # convertir s a flotante
	mul.s 	$f6, $f4, $f4
	mul.s 	$f6, $f6, $f4
	mul.s 	$f6, $f20, $f6
	mul.s 	$f7, $f4, $f4
	mul.s 	$f7, $f21, $f7
	mul.s 	$f8, $f22, $f4
	add.s 	$f24, $f6, $f7
	add.s 	$f24, $f24, $f8
	add.s 	$f24, $f24, $f23

	l.s			$f13, uno
	add.s 	$f4, $f4, $f13

	li			$t0, 1
	add 		$s0, $s0, $t0   


	l.s 		$f10, limite
	c.lt.s 	$f24, $f10
	bc1t 		for
	
	li 			$v0, 4
	la			$a0, funcion1
	syscall

	li			$t0, 1
	sub 		$t0, $t0, $s0  
	li			$v0, 1
	syscall

	li 			$v0, 4
	la			$a0, funcion2
	syscall

	li			$v0, 3
	mov.s 	$f0, $f24
	syscall

	b 			for
#    if (f >= 2.1)
#      std::cout << "\nf(" << x << ") = " << f
for_fin:
#  std::cout << "\n\nTermina el programa\n";
#}
	li 			$v0, 4
	la			$a0, funcion2
	syscall
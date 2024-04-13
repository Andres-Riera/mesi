# Solución PR3 curso 23-24
# Manejo de matrices con funciones
# Autor: Andrés David Riera Rivera
# Fecha última modificación: 13/04/2024

#typedef struct {
#  int nFil;
nFil = 0	# El desplazamiento al campo dentro de la estructura
#  int nCol;
nCol = 4	# El desplazamiento al campo dentro de la estructura
#  float elementos[];
elementos = 8	# El desplazamiento al campo dentro de la estructura
#} structMat;
#

sizeF = 4	# Numero de bytes de un float
LF = 10		# Caracter salto de línea
	.data
#structMat mat1 {
#  6,
#  6,
#  {
#    11.11, 12.12, 13.13, 14.14, 15.15, 16.16,
#    21.21, 22.22, 23.23, 24.24, 25.25, 26.26,
#    31.31, 32.32, 33.33, 34.34, 35.35, 36.36,
#    41.41, 42.42, 43.43, 44.44, 45.45, 46.46,
#    51.51, 52.52, 53.53, 54.54, 55.55, 56.56,
#    61.61, 62.62, 63.63, 64.64, 65.65, 66.66
#  }
#};
mat1:	.word	6
	.word	6
	.float	11.11, 12.12, 13.13, 14.14, 15.15, 16.16,
	.float	21.21, 22.22, 23.23, 24.24, 25.25, 26.26,
	.float	31.31, 32.32, 33.33, 34.34, 35.35, 36.36,
	.float	41.41, 42.42, 43.43, 44.44, 45.45, 46.46,
	.float	51.51, 52.52, 53.53, 54.54, 55.55, 56.56,
	.float	61.61, 62.62, 63.63, 64.64, 65.65, 66.66

#structMat mat2 {
#  7,
#  10,
#  {
#    -36.886, -58.201,  78.671,  19.092, -50.781,  33.961, -59.511, 12.347,  57.306,  -1.938,
#    -86.858, -81.852,  54.623, -22.574,  88.217,  64.374,  52.312, 47.918, -83.549,  19.041,
#     4.255, -36.842,  82.526,  27.394,  56.527,  39.448,  18.429, 97.057,  76.933,  14.583,
#    67.79 ,  -9.861, -96.191,  32.369, -18.494, -43.392,  39.857, 80.686, -36.87 , -17.786,
#    30.073,  89.938,  -6.889,  64.601, -85.018,  70.559, -48.853, -62.627, -60.147,  -5.524,
#    84.323, -51.718,  93.127, -10.757,  32.119,  98.214,  69.471, 73.814,   3.724,  57.208,
#    -41.528, -17.458, -64.226, -71.297, -98.745,   7.095, -79.112, 33.819,  63.531, -96.181
#  }
#};
mat2:	.word	7
	.word	10
	.float	-36.886, -58.201,  78.671,  19.092, -50.781,  33.961, -59.511, 12.347,  57.306,  -1.938,
	.float	-86.858, -81.852,  54.623, -22.574,  88.217,  64.374,  52.312, 47.918, -83.549,  19.041,
	.float	4.255, -36.842,  82.526,  27.394,  56.527,  39.448,  18.429, 97.057,  76.933,  14.583,
	.float	67.79 ,  -9.861, -96.191,  32.369, -18.494, -43.392,  39.857, 80.686, -36.87 , -17.786,
	.float	30.073,  89.938,  -6.889,  64.601, -85.018,  70.559, -48.853, -62.627, -60.147,  -5.524,
	.float	84.323, -51.718,  93.127, -10.757,  32.119,  98.214,  69.471, 73.814,   3.724,  57.208,
	.float	-41.528, -17.458, -64.226, -71.297, -98.745,   7.095, -79.112, 33.819,  63.531, -96.181

# structMat mat3 {
#   1,
#   8,
#   {
#     -36.52,  35.3 ,  79.05, -58.69, -55.23, -19.44, -88.63, -93.61
#   }
# };
mat3:	.word	1
	.word	8
	.float	-36.52,  35.3 ,  79.05, -58.69, -55.23, -19.44, -88.63, -93.61

# structMat mat4 {
#   16,
#   1,
#   { -90.57, -65.11, -58.21, -73.23, -89.38, -79.25,  16.82,  66.3 ,
#     -96.14, -97.16, -24.66,   5.27, -33.5 , -13.09,  27.13, -74.83 }
# };
mat4:	.word	16
	.word	1
	.float	-90.57, -65.11, -58.21, -73.23, -89.38, -79.25,  16.82,  66.3
	.float	-96.14, -97.16, -24.66,   5.27, -33.5 , -13.09,  27.13, -74.83

# structMat mat5 {
#   1,
#   1,
#   { 78.98 }
# };
mat5:	.word	1
	.word	1
	.float	78.98

# structMat mat6 {
#   0,
#   0,
#   { 0 }
# };
mat6:	.word	0
	.word	0
	.float	0.0

#float infinito = INFINITY;
infinito:	.word	0x7F800000

# Cadenas de caracteres
str_titulo:	.asciiz	"\nComienza programa manejo matrices con funciones\n"
str_menu:	.ascii	"(0) Terminar el programa\n"
		.ascii	"(1) Cambiar la matriz de trabajo\n"
		.ascii	"(3) Cambiar el valor de un elemento\n"
		.ascii	"(4) Intercambiar un elemento con su opuesto\n"
		.ascii	"(7) Encontrar el minimo\n"
		.asciiz	"\nIntroduce opción elegida: "
str_errorOpc:	.asciiz	"Error: opcion incorrecta\n"
str_termina:	.asciiz	"\nTermina el programa\n"
str_elijeMat:	.asciiz	"\nElije la matriz de trabajo (1..6): "
str_numMatMal:	.asciiz	"Numero de matriz de trabajo incorrecto\n"
str_errorFil:	.asciiz	"Error: dimension incorrecta.  Numero de fila incorrecto\n"
str_errorCol:	.asciiz	"Error: dimension incorrecta.  Numero de columna incorrecto\n"
str_indFila:	.asciiz	"\nIndice de fila: "
str_indCol:	.asciiz	"Indice de columna: "
str_nuevoValor:	.asciiz	"Nuevo valor para el elemento: "
str_valMin:	.asciiz	"\nEl valor minimo esta en ("
str_conValor:	.asciiz	") con valor "

str_matTiene:	.asciiz	"\n\nLa matriz tiene dimension "

	.text

# void print_mat(structMat* mat) {
print_mat:	# $a0 -> $s0 dirección base de la matriz
# nFil -> $s1
# nCol -> $s2
# elem -> 8($s0)
# f -> $s3
# c -> $s4

#PUSH de ra, s0, s1, s2, s3, s4 = 6 * 4 = 24
	addi $sp, $sp, -24
	sw 	 $s0, 0($sp)
	sw 	 $s1, 4($sp)
	sw 	 $s2, 8($sp)
	sw 	 $s3, 12($sp)
	sw 	 $s4, 16($sp)
	sw 	 $ra, 20($sp)

	move	$s0, $a0 # elem

#   int nFil = mat->nFil;
	lw 		$s1, nFil($s0)
#   int nCol = mat->nCol;
	lw		$s2, nCol($s0)
#   float* elem = mat->elementos;
	addi	$s0, $s0, elementos

#   std::cout << "\n\nLa matriz tiene dimension " << nFil << 'x' << nCol << '\n';
	li 		$v0, 4
	la 		$a0,	str_matTiene # "\n\nLa matriz tiene dimension "
	syscall
	
	li 		$v0, 1
	move	$a0, $s1	# nFil
	syscall

	li 		$v0, 11
	li 		$a0, 'x'
	syscall

	li 		$v0, 1
	move	$a0, $s2	# nCol
	syscall

	li 		$v0, 11
	li 		$a0, LF
	syscall

	li 		$s3, 0 # int f = 0

#   for(int f = 0; f < nFil; f++) {
	bucle_print_mat1:
		bge $s3, $s1, bucle_print_mat1_fin
		
		li 	$s4, 0 # int c = 0		

#     for(int c = 0; c < nCol; c++) {
	bucle_print_mat2:
		bge $s4, $s2,bucle_print_mat2_fin
#       std::cout << elem[f*nCol + c] << ' ';
		mul	$t0, $s3, $s2
		add $t0, $t0, $s4

		mul	$t0, $t0, sizeF
		add $t0, $s0, $t0

		l.s $f12,0($t0)
		li $v0, 2
		syscall

		li $v0, 11
		li $a0, ' '
		syscall

		# incremento de c
		addi $s4, $s4, 1
		b bucle_print_mat2

#     }
	bucle_print_mat2_fin:
#     std::cout << '\n';
		li $v0, 11
		li $a0, LF
		syscall
		
		# incremento de Ff
		addi $s3, $s3, 1
		b bucle_print_mat1
#   }
	bucle_print_mat1_fin:
#   std::cout << '\n';
		li $v0, 11
		li $a0, LF
		syscall
# }

print_mat_fin:
	#POP de ra, s0, s1, s2, s3, s4 = 6 * 4 = 24
	lw 	 $s0, 0($sp)
	lw 	 $s1, 4($sp)
	lw 	 $s2, 8($sp)
	lw 	 $s3, 12($sp)
	lw 	 $s4, 16($sp)
	lw 	 $ra, 20($sp)
	
	addi $sp, $sp, 24
	
	jr	$ra


# void change_elto(structMat* mat, int indF, int indC, float valor) {
change_elto: # $a0 dirección base de la matriz
						 # $a1 indF
						 # $a2 indC
						 # $f12 valor
#   int numCol = mat->nCol;
	lw 		$t0, nCol($a0)
#   mat->elementos[indF * numCol + indC] = valor;
	addi 	$a0,	$a0, elementos
	mul 	$t1, $a1, $t0
	add		$t1, $t1, $a2
	mul		$t1, $t1, sizeF
	add		$a0, $a0, $t1

	swc1	$f12,0($a0)

change_elto_fin:
# }
	jr		$ra

# void swap(float* e1, float* e2) {
swap: # $a0 dirección de e1
			# $a1 dirección de e2

# Asignación registros
# temp1 -> $f4
# temp2 -> $f5

#   float temp1 = *e1;
	l.s		$f4, 0($a0)
#   float temp2 = *e2;
	l.s		$f5, 0($a1)
#   *e1 = temp2;
	swc1	$f5, 0($a0)
#   *e2 = temp1;
	swc1	$f4, 0($a1)
# }
swap_fin:
	jr		$ra

# void intercambia(structMat* mat, int indF, int indC) {
intercambia: # $a0 -> $s0 dirección base de la matriz
						 # $a1 indF
						 # $a2 indC
						 # numCol -> $s2
						 # numFil -> $s1
						 # e1 -> $t1
						 # e2 -> $t2

#PUSH de ra, s0, s1, s2 = 4 * 4 = 16
	addi 	$sp, $sp, -16
	sw 	 	$s0, 0($sp)
	sw 	 	$s1, 4($sp)
	sw 	 	$s2, 8($sp)
	sw 		$ra, 12($sp)

#   int numCol = mat->nCol;
	lw		$s2, nCol($a0)
#   int numFil = mat->nFil;
	lw		$s1, nFil($a0)
#   float* datos = mat->elementos;
	move	$s0, $a0
	addi	$s0, $s0, elementos
#   float* e1 = &datos[indF * numCol + indC];
	mul 	$t0, $a1, $s2 # indF * numCol
	add		$t0, $t0, $a2 # indF * numCol + indC
	mul		$t0, $t0, sizeF

	move 	$t1, $s0
	add		$t1, $t1, $t0 # e1 = &datos[indF * numCol + indC]
#   float* e2 = &datos[(numFil - indF - 1) * numCol + (numCol - indC - 1)];
	sub 	$t0, $s1, $a1 # numFil - indF
	addi	$t0, $t0, -1  # numFil - indF - 1
	mul		$t0, $t0, $s2 # (numFil - indF - 1) * numCol
	sub		$t3, $s2, $a2 # numCol - indC
	addi 	$t3, $t3, -1	# numCol - indC - 1
	add		$t0, $t0, $t3 # (numFil - indF - 1) * numCol + (numCol - indC - 1)
	mul		$t0, $t0, sizeF
	
	move 	$t2, $s0
	add		$t2, $t2, $t0 # e2 = &datos[(numFil - indF - 1) * numCol + (numCol - indC - 1)]

#   swap(e1, e2);
	move	$a0, $t1
	move	$a1, $t2
	
	jal		swap
# }
intercambia_fin:
#POP de ra, s0, s1, s2 = 4 * 4 = 16
	lw 	 	$s0, 0($sp)
	lw 	 	$s1, 4($sp)
	lw 	 	$s2, 8($sp)
	lw 	 	$ra, 12($sp)
	addi	$sp, $sp, 16

	jr	 	$ra

# std::tuple<float, int, int> find_min(structMat* mat) {
find_min:
#	mat -> $a0
# float retorno (min) -> $f0
# int retorno (fmin) -> $v0
# int retorno (cmin) -> $v1
# numCol -> $t0
# numFil -> $t1
# datos -> elementos($a0)
# min -> $f4
# fmin -> $t2
# cmin -> $t3
# f -> $t4
# c -> $t5
# valor -> $f5

#   int numCol = mat->nCol;
	lw		$t0, nCol($a0)
#   int numFil = mat->nFil;
	lw		$t1, nFil($a0)
#   float* datos = mat->elementos;
	addi 	$a0, $a0, elementos
#   float min = infinito;
	lw			$t7, infinito
	mtc1		$t7, $f4
#   int fmin = -1;
	li		$t2, -1
#   int cmin = -1;
	li		$t3, -1
#   for(int f = 0; f < numFil; f++) {
	li		$t4, 0
	bucle_find_min1:
		bge	$t4, $t1, find_min_fin
		li	$t5, 0
#     for(int c = 0; c < numCol; c++) {
	bucle_find_min2:
		bge	$t5, $t0, bucle_find_min2_fin
#       float valor = datos[f * numCol + c];
		mul $t6, $t4, $t0		# f * numCol
		add $t6, $t6, $t5		# f * numCol + c
		mul $t6, $t6, sizeF
		add $a0, $a0, $t6		# $a0 apunta a la dirección del valor
		l.s $f5, 0($a0)			# valor = datos[f * numCol + c];
		sub $a0, $a0, $t6		# $a0 vuelve a apuntar al primer elemento
#       if (valor < min) {
	if_find_min:
		c.le.s	$f4, $f5
		bc1t		if_find_min_fin
#         min = valor;
		mov.s		$f4, $f5
#         fmin = f;
		move		$t2, $t4
#         cmin = c;
		move		$t3, $t5	
#       }
	if_find_min_fin:
		addi	$t5, $t5, 1 # c++
		b			bucle_find_min2
#     }
	bucle_find_min2_fin:
		addi	$t4, $t4, 1 # f++
		b 		bucle_find_min1
#   }
find_min_fin:
#   return {min, fmin, cmin};
	mov.s	$f0, $f4
	move	$v0, $t2
	move	$v1, $t3
	
	jr		$ra
# }
	

# int main() {
main:
# Asignación registros
# matTrabajo -> $s0
# opcion -> $s3
# indFil -> $s1
# indCol -> $s2
# float valorMin -> $f20
# int filaMin -> $s3
# int columnaMin -> $s4

#   std::cout << std::fixed << std::setprecision(8);  // Ignorar
#   std::cout << "\nComienza programa manejo matrices con funciones\n";
	li	$v0, 4
	la	$a0, str_titulo
	syscall
#   structMat* matTrabajo = &mat1;
	la	$s0, mat1
#   while(true) {
while_true:
#     print_mat(matTrabajo);
	move 	$a0, $s0
	jal	print_mat
#     std::cout <<
#     "(0) Terminar el programa\n"
#     "(1) Cambiar la matriz de trabajo\n"
#     "(3) Cambiar el valor de un elemento\n"
#     "(4) Intercambiar un elemento con su opuesto\n"
#     "(7) Encontrar el minimo\n"
#     "\nIntroduce opción elegida: ";
	li	$v0, 4
	la	$a0, str_menu
	syscall
#     int opcion;
#     std::cin >> opcion;
	li $v0, 5
	syscall
	move $s3, $v0

if_condiciones:
#     if(opcion == 0) {
#       break;
#     }
	beqz	$s3, while_true_fin
	beq		$s3, 1, opcion_1
	beq 	$s3, 3, opcion_3_y_4
	beq 	$s3, 4, opcion_3_y_4
	beq		$s3, 7, opcion_7
	b 		opcion_incorrecta

#     // Opción 1 ////////////////////////////////////////////////////////////
opcion_1:
#     if(opcion == 1) {
#       std::cout << "\nElije la matriz de trabajo (1..6): ";
	li $v0, 4
	la $a0, str_elijeMat
	syscall
#       int matT;
#       std::cin >> matT;
	li $v0, 5
	syscall
	move $t2, $v0

	opcion_1_if_condiciones:
		beq 	$t2, 1, if_mat1
		beq		$t2, 2, if_mat2
		beq 	$t2, 3, if_mat3
		beq 	$t2, 4, if_mat4
		beq		$t2, 5, if_mat5
		beq		$t2, 6, if_mat6
		b 		if_mat_incorrecto
#       if (matT == 1) {
	if_mat1:
#         matTrabajo = &mat1;
#         continue;  // volvemos al principio del bucle
		la $s0, mat1
		b while_true
#       }
#       if (matT == 2) {
	if_mat2:
#         matTrabajo = &mat2;
#         continue;  // volvemos al principio del bucle
		la $s0, mat2
		b while_true
#       }
#       if (matT == 3) {
	if_mat3:
#         matTrabajo = &mat3;
#         continue;  // volvemos al principio del bucle
		la $s0, mat3
		b while_true
#       }
#       if (matT == 4) {
	if_mat4:
#         matTrabajo = &mat4;
#         continue;  // volvemos al principio del bucle
		la $s0, mat4
		b while_true
#       }
#       if (matT == 5) {
	if_mat5:
#         matTrabajo = &mat5;
#         continue;  // volvemos al principio del bucle
		la $s0, mat5
		b while_true
#       }
#       if (matT == 6) {
	if_mat6:
#         matTrabajo = &mat6;
#         continue;  // volvemos al principio del bucle
		la $s0, mat6
		b while_true
#       }
	if_mat_incorrecto:
#       std::cout << "Numero de matriz de trabajo incorrecto\n";
		li $v0, 4
		la $a0, str_numMatMal
		syscall
#       continue;  // volvemos al principio del bucle
		b while_true
#     }

#     // Opción 3  y  4 //////////////////////////////////////////////////////////
opcion_3_y_4:
#     if(opcion == 3 || opcion == 4) {
#       std::cout << "\nIndice de fila: ";
		li $v0, 4
		la $a0, str_indFila
		syscall
#       int indFil;
#       std::cin >> indFil;
		li $v0, 5
		syscall
		move $s1, $v0
#       if ((indFil < 0) || (indFil >= matTrabajo->nFil)) {
if_indFil:
		bltz	$s1, if_indFil_then
		lw		$t0, nFil($s0)
		bge		$s1, $t0, if_indFil_then
		b 		if_indFil_fin

		if_indFil_then:  
#         std::cerr << "Error: dimension incorrecta.  Numero de fila incorrecto\n";
			li		$v0, 4
			la 		$a0, str_errorFil
			syscall
#         continue;  // volvemos al principio del bucle
			b 	while_true
#       }
if_indFil_fin:
#       std::cout << "Indice de columna: ";
		li $v0, 4
		la $a0, str_indCol
		syscall
#       int indCol;
#       std::cin >> indCol;
		li $v0, 5
		syscall
		move $s2, $v0
#       if ((indCol < 0) || (indCol >= matTrabajo->nCol)){
if_indCol:
		bltz	$s2, if_indCol_then
		lw		$t0, nCol($s0)
		bge		$s2, $t0, if_indCol_then
		b 		if_indCol_fin

		if_indCol_then:
#         std::cerr << "Error: dimension incorrecta.  Numero de columna incorrecto\n";
			li	$v0, 4
			la	$a0, str_errorCol
			syscall
#         continue;  // volvemos al principio del bucle
			b 	while_true
#       }
if_indCol_fin:
		beq	$s3, 3, opcion3
		beq $s3, 4, opcion4

#       if (opcion == 3) {
	opcion3:
#         std::cout << "Nuevo valor para el elemento: ";
		li 	$v0, 4
		la 	$a0, str_nuevoValor
		syscall
#         float valor;
#         std::cin >> valor;
		li $v0, 6
		syscall
#		change_elto(matTrabajo, indFil, indCol, valor);
		mov.s	$f12, $f0         
		move $a0, $s0
		move $a1, $s1
		move $a2, $s2
		
		jal	change_elto

		b		opcion_3_y_4_fin
#       }
#       if(opcion == 4) {
	opcion4:
#         intercambia(matTrabajo, indFil, indCol);
		move 	$a0, $s0
		move	$a1, $s1
		move	$a2, $s2

		jal intercambia
#       }
opcion_3_y_4_fin:
#       continue;
		b 	while_true
#     }

#     // Opción 7 ////////////////////////////////////////////////////////////
opcion_7:
#     if(opcion == 7) {
#       float valorMin;
#       int filaMin;
#       int columnaMin;
#       std::tie(valorMin, filaMin, columnaMin) = find_min(matTrabajo);
	move		$a0, $s0
	jal find_min
	mov.s		$f20, $f0
	move		$s3, $v0
	move		$s4, $v1
#       std::cout << "\nEl valor minimo esta en (" << filaMin << ','
	li			$v0, 4
	la			$a0, str_valMin # "\nEl valor minimo esta en ("
	syscall

	li			$v0, 1
	move		$a0, $s3 # filaMin
	syscall

	li			$v0, 11
	li			$a0, ','
	syscall
#         << columnaMin <<") con valor " << valorMin;
	li			$v0, 1
	move		$a0, $s4 # columnaMin
	syscall

	li			$v0, 4
	la			$a0, str_conValor # ") con valor "
	syscall

	li			$v0, 2
	mov.s		$f12, $f20 # valoeMin
	syscall
#       continue;
	b				while_true
#     }

#     // Opción Incorrecta ///////////////////////////////////////////////////////
opcion_incorrecta:
#     std::cout << "Error: opcion incorrecta\n";
			li	$v0, 4
			la	$a0, str_errorOpc
			syscall
			b		while_true
#   }
while_true_fin:
#   std::cout << "\nTermina el programa\n";
	li $v0,4
	la $a0,str_termina
	syscall
# }
main_fin:
	li $v0,10
	syscall
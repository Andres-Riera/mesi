# void print_mat(structMat* mat) {
print_mat:	# $a0 dirección base de la matriz
# nFil -> $s1
# nCol -> $s2
# elem -> 8($s0)
# f -> $s3
# c -> $s4

#PUSH de ra, s0, s1, s2, s3, s4, s5 = 7 * 4 = 28
	addi $sp, $sp, -28
	sw 	 $s0, 0($sp)
	sw 	 $s1, 4($sp)
	sw 	 $s2, 8($sp)
	sw 	 $s3, 12($sp)
	sw 	 $s4, 16($sp)
	sw 	 $s5, 20($sp)
	sw 	 $ra, 24($sp)

	move	$s0, $a0 # elem

#   int nFil = mat->nFil;
	lw 		$s1, 0($s0)
#   int nCol = mat->nCol;
	lw		$s2, 4($s0)
#   float* elem = mat->elementos;
	addi	$s0, $s0, 8

#   std::cout << "\n\nLa matriz tiene dimension " << nFil << 'x' << nCol << '\n';
	li 		$v0, 4
	la 		$a0,	str_matTiene
	syscall
	
	li 		$v0, 1
	move	$t0, $s1
	syscall

	li 		$v0, 11
	li 		$a0, 'x'
	syscall

	li 		$v0, 1
	move	$t0, $s2
	syscall

	li 		$v0, 11
	li 		$a0, LF
	syscall

	li 		$s3, 0 # int f = 0

#   for(int f = 0; f < nFil; f++) {
	bucle1:
		bge $s3, $s1, bucle1_fin
		
		li 	$s4, 0 # int c = 0		

#     for(int c = 0; c < nCol; c++) {
	bucle2:
		bge $s4, $s2,bucle2_fin
#       std::cout << elem[f*nCol + c] << ' ';
		mul	$t0, $s3, $s2
		add $t0, $t0, $s4

		li $v0, 1
		syscall

		li $v0, 11
		li $a0, ' '
		syscall

		# incremento de c
		addi $s4, $s4, 1
		b bucle2

#     }
	bucle2_fin:
#     std::cout << '\n';
		li $v0, 11
		li $a0, LF
		syscall
		
		# incremento de Ff
		addi $s3, $s3, 1
		b bucle1
#   }
	bucle1_fin:
#   std::cout << '\n';
		li $v0, 11
		li $a0, LF
		syscall
# }

print_mat_fin:
	#POP de ra, s0, s1, s2, s3, s4, s5 = 7 * 4 = 28
	lw 	 $s0, 0($sp)
	lw 	 $s1, 4($sp)
	lw 	 $s2, 8($sp)
	lw 	 $s3, 12($sp)
	lw 	 $s4, 16($sp)
	lw 	 $s5, 20($sp)
	lw 	 $ra, 24($sp)
	
	addi $sp, $sp, 28
	
	jr	$ra
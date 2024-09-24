# Principio de Computadores. Preparación para el Microexamen
# Operaciones con funciones y direccionamiento indirecto
# Autor: 
# Fecha última modificación: 
#include <iostream>

# const int n1 = 10;
# double v1[n1] = {10.5, 9.5, 7.25, 6.25, 5.75, 4.5, 4.25, 3.5, -1.5, -2.0};
# const int n2 = 5;
# double v2[n2] = {5.5, 4.5, 4.25, 2.5, 2.5 };
# const int n3 = 4;
# double v3[n3] = {7.0, 5.0, 2.0, 1.0};

sizeD = 8
LF = 10
SPACE = 32

    .data
n1:     .word 10
v1:     .double 10.5, 9.5, 7.25, 6.25, 5.75, 4.5, 4.25, 3.5, -1.5, -2.0
n2:     .word 5
v2:     .double 5.5, 4.5, 4.25, 2.5, 2.5
n3:     .word 4
v3:     .double 7.0, 5.0, 2.0, 1.0
cad1:   .asciiz "\nVector con dimension "
cad2:   .asciiz "\nIntentando mezcla con dos vectores ...\n"
cad3:   .asciiz "\nFIN DEL PROGRAMA\n"

    .text

# void printvec(double *v, const int n) {
# Esta función llama a otra -> necesita pila
# v -> $a0 -> $s0
# n -> $a1 -> $s1
# i -> $s2
printvec:
    # PUSH ra, s0, s1, s2  4 * 4 = 16
    addi    $sp, $sp, -16
    sw      $s0, 0($sp)
    sw      $s1, 4($sp)
    sw      $s2, 8($sp)
    sw      $ra, 12($sp)

    move    $s0, $a0
    move    $s1, $a1
    li      $s2, 0
#     for (int i = 0; i < n; i++)
printvec_for:
    bge    $s2, $s1, printvec_for_fin
#         std::cout << v[i] << " ";
    # v[i] -> $f4
    mul     $t0, $s2, sizeD
    addu    $t0, $t0, $s0
    l.d     $f4, 0($t0)

    li      $v0, 3
    mov.d   $f12, $f4
    syscall

    li      $v0, 11
    li      $a0, SPACE
    syscall

    addi    $s2, 1          # i++
    b       printvec_for
printvec_for_fin:    
#     std::cout << "\n";
    li  $v0, 11
    li  $a0, LF
    syscall
#     return;
# }
    # POP ra, s0, s1, s2
    lw      $s0, 0($sp)
    lw      $s1, 4($sp)
    lw      $s2, 8($sp)
    lw      $ra, 12($sp)
    addi    $sp, $sp, 16

    jr      $ra

printvec_fin:


# int ordenado(double *v, const int n) {
# v -> a0
# n -> a1
# parametro de salida entero -> v0
# resultado -> v0
# i -> t4
ordenado:
#     int resultado = 1;
    li  $v0, 1
#     int i = 0;
    li  $t4, 0
#     while (i < n-1) {
    move $t2, $a1
    addi $t2, $t2, -1
while_ordenado:
    bge $t2, $t4, while_ordenado_fin
#         if (v[i+1] >= v[i]) {
if_ordenado:
    addi $t3, $t4, 1
    mul  $t3, $t3, sizeD
    add  $t0, $t3, $a0
    l.d  $f4, 0($t0)

    mul  $t5, $t4, sizeD
    add  $t6, $t5, $a0
    l.d  $f6, 0($t6)

    c.lt.d $f6, $f4
    bc1f   if_ordenado_fin
#             resultado = 0;
    li  $v0, 0
#             break;
    b   while_ordenado_fin
#         }
if_ordenado_fin:
#         i++;
    addi    $t4, 1
    b   while_ordenado
#     }
while_ordenado_fin:
#     return resultado;
    jr  $ra
# }
ordenado_fin:

# void merge(double *v1, const int n1,double *v2, const int n2) {
# Función que llama a otra -> necesita pila
# v1 -> a0 -> s0
# n1 -> a1 -> s1
# v2 -> a2 -> s2
# n2 -> a3 -> s3

# o1 -> t1
# o2 -> t2
# i -> s4
# j -> s5
merge:
    # PUSH ra, s0, s1, s2, s3, s4, s5: 7 * 4 = 28
    # PUSH ra, s0, s1, f20.d, f22.d: 3 * 4 + 2 * 8 = 28
    addi    $sp,$sp,-28
    sw      $s0,0($sp)
    sw      $s1,4($sp)
    sw      $s2,8($sp)
    sw      $s3,12($sp)
    sw      $s4,16($sp)
    sw      $s5,20($sp)
    sw      $ra, 24($sp)

    move    $s0, $a0
    move    $s1, $a1
    move    $s2, $a2
    move    $s3, $a3
#     int  o1 = ordenado(v1,n1);
    move    $a0, $s0
    move    $a1, $s1
    jal     ordenado
    move    $t1, $v0
#     if (o1 == 0) return;
    beq     $t1, 0, merge_return
#     int o2 = ordenado(v2,n2);
    move    $a0, $s2
    move    $a1, $s3
    jal     ordenado
    move    $t2, $v0
#     if (o2 == 0) return;
    beq     $t2, 0, merge_return
#     int i = 0; // índice para recorrer el v1
    li      $s4, 0
#     int j = 0; // índice para recorrer el v2
    li      $s5, 0
#     while ( ( i < n1) && (j < n2) ) {
merge_while:
    ble     $s1, $s4, merge_while2
    ble     $s3, $s5, merge_while2
#         if (v1[i] >= v2[j]) {
    mul $t5, $s4, sizeD
    add $t5, $t5, $s0
    l.d $f4, 0($t5)

    mul $t6, $s4, sizeD
    add $t6, $t6, $s2
    l.d $f6, 0($t6)

    c.lt.d  $f6, $f4
    bc1t    merge_while_else
#             std::cout << v1[i] << " ";
    li  $v0, 3
    mov.d $f12, $f4
    syscall

    li $v0, 11
    li $a0, ' '
    syscall
#             i++;
    addi $s4, $s4, 1
    b   merge_while
#         }
#         else {
merge_while_else:
#             std::cout << v2[j] << " ";
    li  $v0, 3
    mov.d $f12, $f6
    syscall

    li $v0, 11
    li $a0, ' '
    syscall
#             j++;
    addi $s5, $s5, 1
    b   merge_while
#         }
#     }
#     while ( i < n1) {
merge_while2:
    ble $s1, $s4, merge_while3
#         std::cout << v1[i] << " ";
    mul $t0, $s4, sizeD
    add $t0, $t0, $s0
    l.d $f4, 0($t0)

    li  $v0, 3
    mov.d $f12, $f4
    syscall

    li  $v0, 11
    li  $a0, ' '
    syscall
#         i++;
    addi $s4, $s4, 1
    b   merge_while2
#     }

#     while ( j < n2) {
merge_while3:
    ble $s3, $s5, merge_while3_fin
#         std::cout << v2[j] << " ";
    mul $t0, $s5, sizeD
    add $t0, $t0, $s2
    l.d $f4, 0($t0)
#         j++;
    addi $s5, $s5, 1
    b   merge_while3
#     }
merge_while3_fin:
#     std::cout << "\n";
    li  $v0, 11
    li  $a0, LF
    syscall
#     return;
merge_return:
# }
    # POP ra, s0, s1, f20.d, f22.d: 3 * 4 + 2 * 8 = 28
    lw      $s0,0($sp)
    lw      $s1,4($sp)
    lw      $s2,8($sp)
    lw      $s3,12($sp)
    lw      $s4,16($sp)
    lw      $s5,20($sp)
    lw      $ra, 24($sp)
    addi    $sp,$sp,28

    jr      $ra

merge_fin:

# int main(void) {
main:
#     std::cout << "\nVector con dimension " << n1 << std::endl;
    li  $v0, 4
    la  $a0, cad1
    syscall

    li  $v0, 1
    lw  $a0, n1
    syscall

    li  $v0, 11
    li  $a0, LF
    syscall
#     printvec(v1,n1);
    la $a0, v1
    lw $a1, n1
    jal  printvec
#     std::cout << "\nVector con dimension " << n2 << std::endl;
    li  $v0, 4
    la  $a0, cad1
    syscall

    li  $v0, 1
    lw  $a0, n2
    syscall

    li  $v0, 11
    li  $a0, LF
    syscall
#     printvec(v2,n2);
    la $a0, v2
    lw $a1, n2
    jal  printvec
#     std::cout << "\nVector con dimension " << n3 << std::endl;
    li  $v0, 4
    la  $a0, cad1
    syscall

    li  $v0, 1
    lw  $a0, n3
    syscall

    li  $v0, 11
    li  $a0, LF
    syscall
#     printvec(v3,n3);
    la $a0, v3
    lw $a1, n3
    jal  printvec
#     std::cout << "\nIntentando mezcla con dos vectores ...\n";
    li  $v0, 4
    la  $a0, cad2
    syscall
#     merge(v1,n1,v2,n2);
    la $a0, v1
    lw $a1, n1
    la $a2, v2
    lw $a3, n2
    jal merge
#     std::cout << "\nIntentando mezcla con dos vectores ...\n";
    li  $v0, 4
    la  $a0, cad2
    syscall
#     merge(v1,n1,v3,n3);
    la $a0, v1
    lw $a1, n1
    la $a2, v3
    lw $a3, n3
    jal merge
#     std::cout << "\nFIN DEL PROGRAMA\n";
    li  $v0, 4
    la  $a0, cad3
    syscall
#     return(0);
# }
    li  $v0, 10
    syscall


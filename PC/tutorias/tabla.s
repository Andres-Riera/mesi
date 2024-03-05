.data
por:           .asciiz " x "
str_introduzca: .asciiz "Introduzca un numero: "
igual:         .asciiz " = "
str_salto:     .asciiz "\n"
str_termina:   .asciiz "Fin de ejecución\n"

.text
main:
    li      $v0, 4
    la      $a0, str_introduzca
    syscall

    li      $v0, 5
    syscall
    move    $s0, $v0

    li      $t0, 1
    move    $s1, $t0

for:
    ble     $s1, 10, for_dentro  # Salta dentro del bucle si $s1 es menor o igual a 10
    j       for_fin              # Salta al final del bucle si $s1 es mayor que 10

for_dentro:
    mul     $s2, $s0, $s1
    li      $v0, 1
    move    $a0, $s0
    syscall
    
    li      $v0, 4
    la      $a0, por
    syscall

    li      $v0, 1
    move    $a0, $s1
    syscall

    li      $v0, 4
    la      $a0, igual
    syscall

    li      $v0, 1
    move    $a0, $s2
    syscall

    li      $v0, 4
    la      $a0, str_salto
    syscall

    addi    $s1, $s1, 1  # Incrementa el contador
    j       for           # Salta de nuevo al inicio del bucle

for_fin:
    # Imprime mensaje de fin de ejecución
    li      $v0, 4
    la      $a0, str_termina
    syscall

    # Salida del programa
    li      $v0, 10
    syscall

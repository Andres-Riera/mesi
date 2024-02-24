.data
str_titulo:     .asciiz "Numeros primos\n"
str_introduzca: .asciiz "Introduzca un numero"
str_divisible:  .asciiz "El número es divisible por "
str_salto:      .asciiz "\n"
str_esprimo:    .asciiz "Es primo\n"
str_termina:    .asciiz "Fin de ejecución\n"

    .text
main:   
    li      $v0,4
    la      $a0,str_titulo
    syscall

do_while:
    li      $v0,4
    la      $a0,str_introduzca
    syscall

    li      $v0,5
    syscall
    move    $s0,$v0
ifn0:
    bne     $s0,$zero,ifn0_fin
    b       do_while_fin
ifm0_fin:
do_while_condicion:
    bne     $s0,$zero,do_while
do_while_fin:

    li      $v0,10
    syscall
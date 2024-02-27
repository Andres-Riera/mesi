# PR1. PRINCIPIO DE COMPUTADORES.
# Autor: Andrés David Riera Rivera
# Fecha última modificación: 27/02/24

.data

titulo:      .asciiz "\nPR1: Principio de computadores.\n"
pet:         .asciiz "\nIntroduzca maximo error permitido: "
caderr:      .asciiz "\nError: el dato introducido debe cumplir 0.00001 <= dato < 1\n"
cade:        .asciiz "\nNumero e: "
cadnt:       .asciiz "\nNumero de terminos: "
cadfin:      .asciiz "\nPR1: Fin del programa.\n"
min_error:   .double 0.00001
max_error:   .double 1.0
uno:         .double 1.0

.text

main:

    li $v0, 4
    la $a0, titulo
    syscall
    li $v0, 4
    la $a0, pet
    syscall
    li $v0, 7                
    syscall
    mov.d $f2, $f0            # Maximo error permitido

while_condicion1:

    l.d $f4, min_error
    l.d $f6, max_error
    c.lt.d $f2, $f4      
    bc1t while1
    c.le.d $f6, $f2      
    bc1t while1
    b while_fin1


while1:

    li $v0, 4
    la $a0, caderr
    syscall
    li $v0, 4
    la $a0, pet
    syscall
    li $v0, 7                
    syscall
    mov.d $f2, $f0
    b while_condicion1

while_fin1:

    l.d $f8, uno
    mov.d $f10, $f8           # Numero e
    mov.d $f12, $f8           # Factorial
    mov.d $f14, $f8           # Ultimo termino
    mov.d $f16, $f8           # Numero de terminos 

while_condicion2:

    c.lt.d $f2, $f14
    bc1f while_fin2

while2:

    mul.d $f12, $f12, $f16
    div.d $f14, $f8, $f12
    add.d $f10, $f10, $f14
    add.d $f16, $f16, $f8
    j while_condicion2

while_fin2:

    li $v0, 4
    la $a0, cade
    syscall
    li $v0, 3                
    mov.d $f12, $f10
    syscall
    li $v0, 4
    la $a0, cadnt
    syscall
    li $v0, 3                
    mov.d $f12, $f16
    syscall
    li $v0, 4
    la $a0, cadfin
    syscall
    li $v0, 10
    syscall

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
    # Imprime el titulo
    li $v0, 4
    la $a0, titulo
    syscall
    # Imprime la cadena que pide el maximo error permitido
    li $v0, 4
    la $a0, pet
    syscall
    # std::cin >> error
    li $v0, 7                
    syscall
    mov.d $f2, $f0            # Maximo error permitido

while_condicion1:
    # while(0.0001 < error ||  error >= 1
    l.d $f4, min_error
    l.d $f6, max_error
    c.lt.d $f2, $f4      
    bc1t while1
    c.le.d $f6, $f2      
    bc1t while1
    b while_fin1 # Mientras el error esté fuera del rango permitido salta al bucle while


while1:
    # Vuelve a pedir el valor del error
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

    l.d $f8, uno              # Cargamos en $f8 el valor 1.0
    mov.d $f22, $f8           # Numero e
    mov.d $f12, $f8           # Factorial
    mov.d $f14, $f8           # Ultimo termino
    mov.d $f24, $f8           # Numero de terminos 

while_condicion2:
    # while (ultimo >= error)
    c.le.d $f2, $f14
    bc1f while_fin2

while2:

    mul.d $f12, $f12, $f24  # factorial = factorial * n_terminos
    div.d $f14, $f8, $f12   # ultimo = 1.0 / factorial
    add.d $f22, $f22, $f14  # e = e + ultimo
    add.d $f24, $f24, $f8   # n_terminos = n_terminos + 1.0
    b while_condicion2

while_fin2:
    # Imprimir valor de e
    li $v0, 4
    la $a0, cade
    syscall
    li $v0, 3                
    mov.d $f12, $f22
    syscall
    # Imprimir numero de terminos
    li $v0, 4
    la $a0, cadnt
    syscall
    cvt.w.d $f24, $f24 # Convertir de doble precision a entero
    mfc1 $t0, $f24
    li $v0, 1    
    move $a0, $t0
    syscall
    # Imprimir fin del programa
    li $v0, 4
    la $a0, cadfin
    syscall
.data 
	array:  .word  10, 20, 30, 40, 50    # Array of 5 integers initialized with values
	integer1: .word 30
	integer2: .word 60
	found: .asciz "Number found in array! "
	Notfound: .asciz "Number not found in array! "
	
.text 
.globl main

main:
	la a0, integer1
	
	call search
	
search:
	la t0, array
	li t1, 5
	li t2, 0 
	
loop:
	blt t1, t2, printNotFound
	beq t0, a0, printFound
	addi t0, t0, 4
	addi t2, t2, 1
	j loop
	
	
printFound:
	add s0, x0, a0
	la a0, found
	li a7, 4
	ecall
	
	add a0, x0, s0
	li a7, 1
	ecall
	
	li a7, 10
	ecall


printNotFound:
	add s0, x0, a0
	la a0, Notfound
	li a7, 4
	ecall
	
	add a0, x0, s0
	li a7, 1
	ecall
	
	li a7, 10
	ecall
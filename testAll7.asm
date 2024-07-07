.data 
	result: .asciz "The Factorial result is: "
	
.text 
.globl main

main:
	
	li a0, 3
	
	call factorial
	call print
	
factorial:
	li t0, 1
	bne a0, t0, recurse
	ret
	
recurse:
	addi sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	addi a0, a0, -1
	call factorial
	lw t1, 4(sp)
	mul a0, t1, a0
	lw ra, 0(sp)
	addi sp, sp, 8
	ret
	
print:
	add s0, x0, a0
	la a0, result
	li a7, 4
	ecall
	
	add a0, x0, s0
	li a7, 1
	ecall
	
	li a7, 10
	ecall
.data 
	integer: .word 4
	result: .asciz "The sum is: "
	
.text
.globl main

main: 
	li a0, 4
	
	jal ra, sum
	jal ra, print
	
	
sum: 
	bne a0, x0, recurse
	jalr x0, ra, 0
	
recurse: 
	addi sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	addi a0, a0, -1	# a0 = n - 1
	jal ra, sum	# sum(n - 1)
	lw t0, 4(sp)
	add a0, a0, t0	# n + sum(n - 1)
	
		
	lw ra, 0(sp)
	addi sp, sp, 8
	jalr x0, ra, 0
	
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

.data 
	integer: .word 6
	output: .asciz "Output = "
	
.text
.globl main

main:
	li s0, 0	# i = 0
	li s1, 3	# e = 3
	li s2, 4	# g = 4
	li s3, 5	# f = 5
	
	slli t0, s2, 1	# t0 = s2 << 1
	slli t1, s3, 3	# t1 = s3 << 3
	slli t2, s3, 2	# t2 = s3 << 2
	add t0, t0, s2
	add t1, t1, t2
	add t1, t1, s3
	add s0, s1, t0
	sub s0, s0, t1	# i = e + 3*g - 13*f
	
print:
	la a0, output
	li a7, 4
	ecall 
	
	add a0, x0, s0
	li a7, 1
	ecall	
	
	li a7, 10
	ecall
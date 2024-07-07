.text
	
	la x10,prompt2
	li a7, 4
	ecall
	li t3, 3
	la x10,int
	li a7, 1
	ecall
#	li t3, 3
	la x10,prompt1
	li a7, 4
	ecall

.data
prompt1: .asciz "Hello world"
int: .word 15
prompt2: .asciz "Nooooooooooo wayyyyy"
.text
.globl main

main:
	li x1, 1
	li x2, 4
	li x3, 284876493
	li x4, -2
	
	xor x5, x1, x2
	or x5, x1, x2
	and x5, x1, x2
	sll x5, x2, x1
	srl x5, x2, x1
	sra x5, x4, x1
	
	bltu x3, x1, true
	nop
	addi x1, x1, 1
	
true:
	addi x3, x0, 0
	slt x3, x3, x2
	li x4, -32847648
	sltu x4, x1, x4
	
	xori x5, x2, 2
	ori x5, x2, 2
	andi x5, x2, 2
	
	srli x5, x2, 2
	srai x5, x2, 2
	
	slti x5, x2, 2
	sltiu x5, x2, 2
	li x3, -384903
	
up:	beq x3, x0, end
	
	nop
	
	bgeu x3, x2, cont
	
cont:
	addi x3, x0, 0

end:
	nop
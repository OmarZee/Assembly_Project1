
	li a0, 3
	
	jal ra, factorial
	
factorial:
	li t0, 1
	bne a0, t0, recurse
	jalr x0, ra, 0
	
recurse:
	addi sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	addi a0, a0, -1
	jal ra, factorial
	lw t1, 4(sp)
	mul a0, t1, a0
	lw ra, 0(sp)
	addi sp, sp, 8
	jalr x0, ra, 0

end: nop
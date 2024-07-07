.data 
	color: .byte 'R', 'G', 'B', 'A'
.text
.globl main

main:
	la a0, color     # Load address of color array into a0
	
	# Load each color component into separate registers
	lb s0, 0(a0)     # s0 = 'R'
	lb s1, 1(a0)     # s1 = 'G'
	lb s2, 2(a0)     # s2 = 'B'
	lb s3, 3(a0)     # s3 = 'A'
	
	# Combine the colors into a single register (s4)
	slli t0, s0, 24  # Move 'R' to the highest byte
	slli t1, s1, 16  # Move 'G' to the second highest byte
	slli t2, s2, 8   # Move 'B' to the third highest byte
	or t0, t0, t1    # Combine R and G
	or t0, t0, t2    # Combine RG and B
	or t0, t0, s3    # Combine RGB and A into t0
	
	add s4, x0, t0       co # Move the combined value to s4
	
	# Printing is not directly possible as an integer with syscall 4, so we skip it
	# Assuming a suitable way to print would be used in real code (e.g., converting to string)
	
	add a0, x0, s4

	li a7, 1
	ecall

	# Exit program
	li a7, 10        # Syscall for exit
	ecall

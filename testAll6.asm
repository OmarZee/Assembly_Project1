.data
    array: .byte 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0
    halfArray: .half 0x1234, 0x5678, 0x9ABC, 0xDEF0
.text
.globl main

main:
    la a0, array         # Load address of array into a0
    lbu t0, 1(a0)        # Load unsigned byte from array[1] into t0
    lhu t1, 2(a0)        # Load unsigned halfword from array[2] into t1

    lui t2, 0x12345      # Load upper immediate (20 bits) into t2

    li t3, 10
    li t4, 20
    bltu t3, t4, less    # Branch to less if t3 < t4 (unsigned)
    bgeu t4, t3, greater # Branch to greater if t4 >= t3 (unsigned)

less:
    jal ra, end          # Jump and link to end

greater:
    li t5, 32
    srai t5, t5, 2       # Arithmetic shift right t5 by 2 (t5 = 32 >> 2 = 8)

    li t6, 5
    sltiu t0, t6, 10     # Set t0 to 1 if t6 < 10 (unsigned), else set to 0

end:
    li a7, 10            # Syscall for exit
    ecall

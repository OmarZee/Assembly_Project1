.text
lhu x5, 0(x1)
sh x6, 4(x1)
lbu x5, 0(x1)
sb x6, 0(x5)
bge x5, x6, cont
nop
cont: 
lui x10, 0x87654 # x10 = 0x87654000 
addi x10, x10, 0x321 # x10 = 0x87654321


# Assembly_Project1
The purpose of this report is to document the design, implementation, and usage of a RISC-V Instruction Set Architecture (ISA) Simulator. This simulator is developed to execute RISC-V machine code instructions, mimicking the behavior of a real RISC-V processor. The report covers the construction of the simulator, its usage, design considerations, challenges encountered during development, and limitations of the simulator.

How to build a simulator:

In order to build a simulator that mimics a cpu you will need to utilize a simulated memory array ( memory[ ] ) to store the instructions. In our simulator we made 2 arrays insead of 1, one for the instructions and 1 for the data ( string instruction_arr[16000], string data_arr[16000] )
You also need an array for simulated registers ( int register_arr[32]; In our design we decided to go with 4 bytes in each array index).
A function that decodes the machine code to identify the type, instruction to be executed (R-type, I-type, S-type, B-type, U-type, J-type). 
You need to write functions for each instruction in each type to mimic the function done by the processor after disassembling the machine code.

How to use the simulator:

Open the terminal insert    $ g++ -o rvsim main.cpp 
to compile the code for the simulator after opening in the file of the main program or identifying the path for the program.
Insert    $ ./rvsim test.bin test-data.bin 
to open the file that was extracted from RARS and to run the file disassembling the machine code, writing the instructions in the assembly code then running the code itself of the assembly language. 
The simulator design. Handles the decompressed 32 bits

The challenges that we faced in the project:
Issues with functions like bgeu and bltu because of wrong incrementation with the PC
Issues with reading the .bin file as we did not use the template at the beginning
Wrong immediate values because of assigning wrong values
We tested the code incorrectly when we tried to test the ecall function.
We had many challenges in comparing the immediates to the right machine code in many functions
In various parts of the code, bit manipulation is done directly on strings. It might subjected to error if the value is incorrect.
We faced a challenge in the U-type as our memory held 4 bytes in each index which made the accurate calculations of addresses to be stored for ecalls very challenging. None of the ecalls were working until we figured out an equation to handle addresses properly

Limitations:
Compressed functions are not supported.
The stack pointer seems to be causing infinite loops as it is implemented incorrectly





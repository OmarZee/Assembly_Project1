#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

string instruction_arr[16000];
string data_arr[16000];
string user_string;
int register_arr[32];
int PC=0;       // Program Counter

int binaryToDecimal(string str)
{
    string number = str;
    int decimal = 0;
    int base = 1;
    int length = number.length();

    for (int i = length - 1; i >= 0; i--) 
    {
        if (number[i] == '1')
        {
            decimal += base;
        }
        base = base * 2;
    }
    return decimal;
}
int binaryToSignedDecimal(string str) {
    int decimal = 0;
    int base = 1;
    int length = str.length();
    // Check if the number is negative (two's complement representation)
    bool isNegative = (str[0] == '1');
    // Process the binary string from right to left
    for (int i = length - 1; i >= 0; --i) {
        if (str[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    // Adjust for two's complement if the number is negative
    if (isNegative) {
        decimal -= base;
    }
    return decimal;
}
int binaryToUnsignedDecimal(string str) {
    int decimal = 0;
    int base = 1;
    int length = str.length();
    // Process the binary string from right to left
    for (int i = length - 1; i >= 0; --i) {
        if (str[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

string decimalToBinaryUnsigned(unsigned int num) {
    if (num == 0) return "0";
    string binary = "";
    while (num > 0) {
        if (num % 2 == 0) {
            binary = "0" + binary;
        } else {
            binary = "1" + binary;
        }
        num /= 2;
    }
    return binary;
}

string decimalToBinarySigned(int num){
    string binary;
    if (num < 0) {
        num = -num;
        binary = decimalToBinaryUnsigned(num);
        // Pad the binary string with 0s to make it 32 bits long
        while (binary.length() < 32) {
            binary = "0" + binary;
        }
        // Perform one's complement
        for (int i = 0; i < binary.length(); ++i) {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        // Perform two's complement
        bool carry = true;
        for (int i = binary.length() - 1; i >= 0; --i) {
            if (carry) {
                if (binary[i] == '1') {
                    binary[i] = '0';
                } else {
                    binary[i] = '1';
                    carry = false;
                }
            }
        }
    } else {
        binary = decimalToBinaryUnsigned(num);
        // Pad the binary string with 0s to make it 32 bits long
        while (binary.length() < 32) {
            binary = "0" + binary;
        }
    }
    return binary;
}

// RTYPE
void Rtype(string opcode, int rd_decimal, string func3, int rs1_decimal, int rs2_decimal, string func7)
{
    //cout << "Rtype function" << endl;
    if (func3 == "000") //func3 = 0
    {
        //cout << "func3 checked!" << endl;
        if (func7 == "0000000") //ADD
        {
            //cout << "ADD checked!" << endl;
            register_arr[rd_decimal] = register_arr[rs1_decimal] + register_arr[rs2_decimal];
            cout << "add x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
            cout << "The result of the addition: " << register_arr[rd_decimal] << endl;
        }
        else //SUB
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] - register_arr[rs2_decimal];
            cout << "sub x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
        }
    }
    else if (func3 == "001") //func3 = 1
    {
        register_arr[rd_decimal] = register_arr[rs1_decimal] << register_arr[rs2_decimal];  //SLL
        cout << "sll x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
        cout << "The result of the shift: " << register_arr[rd_decimal] << endl;
    }
    else if (func3 == "010") //func3 = 2
    {

        register_arr[rd_decimal] = register_arr[rs1_decimal] < register_arr[rs2_decimal];  //SLT
        cout << "slt x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the comparison: " << register_arr[rd_decimal] << endl;
    }
    else if (func3 == "011") //func3 = 3
    {
        register_arr[rd_decimal] = register_arr[rs1_decimal] < register_arr[rs2_decimal];  //SLTU
        cout << "sltu x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the comparison: " << register_arr[rd_decimal] << endl;
        // Need to add 0 extension
        
    }
    else if (func3 == "100") //func3 = 4
    {
        register_arr[rd_decimal] = register_arr[rs1_decimal] ^ register_arr[rs2_decimal];  //XOR
        cout << "xor x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
    }
    else if (func3 == "101") //func3 = 5
    {
        if (func7 == "0000000") //SRL
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] >> register_arr[rs2_decimal];
            cout << "srl x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
        }
        else //SRA
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] >> register_arr[rs2_decimal];
            cout << "sra x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            // Need to add sign extension
        }
    }
    else if (func3 == "110") //func3 = 6
    {
        register_arr[rd_decimal] = register_arr[rs1_decimal] | register_arr[rs2_decimal];  //OR
        cout << "or x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
    }
    else if (func3 == "111") //func3 = 7
    {
        register_arr[rd_decimal] = register_arr[rs1_decimal] & register_arr[rs2_decimal];  //AND
        cout << "and x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
    }
    PC++;
}

// ITYPE
void Itype(string opcode, int rd_decimal, string func3, int rs1_decimal, int immediate_decimal, string imm)
{
    if (opcode == "0010011")
    {
        if (func3 == "000") //func3 = 0
        {
            if(rd_decimal == 2){
                register_arr[rd_decimal] = register_arr[rs1_decimal] + immediate_decimal/4;
            }
            else{
                register_arr[rd_decimal] = register_arr[rs1_decimal] + immediate_decimal;  //ADDI
            }
            cout << "addi x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the addition: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "010") //func3 = 2
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] < immediate_decimal;  //SLTI
            cout << "slti x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the comparison: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "011") //func3 = 3
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] < immediate_decimal;  //SLTIU
            cout << "sltiu x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the comparison: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "100") //func3 = 4
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] ^ immediate_decimal;  //XORI
            cout << "xori x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "110") //func3 = 6
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] | immediate_decimal;  //ORI
            cout << "ori x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "111") //func3 = 7
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal] & immediate_decimal;  //ANDI
            cout << "andi x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            PC++;
        }
        else if (func3 == "001") //func3 = 1
        {
            for(int i=0;i<7;i++){
                    imm[i] = '0';
                }
            immediate_decimal = binaryToSignedDecimal(imm);
            register_arr[rd_decimal] = register_arr[rs1_decimal] << immediate_decimal;  //SLLI
            PC++;

            cout << "slli x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
            cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
        }
        else if (func3 == "101") //func3 = 5
        {
            if (opcode == "0010011") //SRLI
            {
                for(int i=0;i<7;i++){
                    imm[i] = '0';
                }
                immediate_decimal = binaryToSignedDecimal(imm);
                register_arr[rd_decimal] = register_arr[rs1_decimal] >> immediate_decimal;
                cout << "Actual immediate = " << immediate_decimal << endl;

                cout << "srli x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
                cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            }
            else //SRAI
            {
                for(int i=0;i<7;i++){
                    imm[i] = '0';
                }
                immediate_decimal = binaryToSignedDecimal(imm);
                register_arr[rd_decimal] = register_arr[rs1_decimal] >> immediate_decimal;
                cout << "Actual immediate = " << immediate_decimal << endl;

                cout << "srai x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
                cout << "The result of the instruction: " << register_arr[rd_decimal] << endl;
            }
            PC++;
        } 
    }
    else if (opcode == "0000011")
    {
        if (func3 == "000") //LB
        {
            string str = decimalToBinarySigned(register_arr[rs1_decimal + immediate_decimal]);  //LB
            for(int i=0; i<24; i++)
            {
                if(str[24] == '1'){
                    str[i] = '1';
                }
                else{
                    str[i] = '0';
                }
            }
            register_arr[rd_decimal] = binaryToSignedDecimal(str);

            cout << "lb x" << rd_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
            cout << "The result of the load: " << register_arr[rd_decimal] << endl;
        }
        else if (func3 == "001") //LH
        {
            string str = decimalToBinarySigned(register_arr[rs1_decimal + immediate_decimal]);  //LH
            for(int i=0; i<16; i++)
            {
                if(str[16] == '1'){
                    str[i] = '1';
                }
                else{
                    str[i] = '0';
                }
            }
            register_arr[rd_decimal] = binaryToSignedDecimal(str);

            cout << "lh x" << rd_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
            cout << "The result of the load: " << register_arr[rd_decimal] << endl;
        }
        else if (func3 == "010") //LW
        {
            register_arr[rd_decimal] = register_arr[rs1_decimal + immediate_decimal];  //LW
            cout << "lw x" << rd_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
            cout << "The result of the addition: " << register_arr[rd_decimal] << endl;
        }
        else if (func3 == "100") //LBU
        {
            string str = decimalToBinaryUnsigned(register_arr[rs1_decimal + immediate_decimal]);  //LBU
            str = "000000000" + str; 
            cout << "str = " << str << endl;
            for(int i=0; i<24; i++)
            {
                str[i] = '0';
            }

            cout << "str = " << str << endl;

            register_arr[rd_decimal] = binaryToUnsignedDecimal(str);

            cout << "lbu x" << rd_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
            cout << "The result of the load: " << register_arr[rd_decimal] << endl;
        }
        else if (func3 == "101") //LHU
        {
            string str = decimalToBinaryUnsigned(register_arr[rs1_decimal + immediate_decimal]);  //LHU
            str = "000000000" + str; 
            cout << "str = " << str << endl;
            for(int i=0; i<16; i++)
            {
                str[i] = '0';
            }

            cout << "str = " << str << endl;

            register_arr[rd_decimal] = binaryToUnsignedDecimal(str);

            cout << "lhu x" << rd_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
            cout << "The result of the load: " << register_arr[rd_decimal] << endl;
        }
        PC++;
    }
    else if (opcode == "1100111")
    {
        if (func3 == "000") // jalr
        {
            register_arr[rd_decimal] = PC + 1;
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 2); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 2) + 1;
            }
        }
        cout << "jalr x" << rd_decimal << ", x" << rs1_decimal << ", " << PC << endl;
        cout << "The result of the jump: " << instruction_arr[PC] << endl;
    }
    else if (opcode == "1110011")
    {
        if (immediate_decimal == 0) // ecall
        {
            if(register_arr[17] == 4){
                cout << "The result of the print: " << to_string(register_arr[10]) << endl;
            }
            else if(register_arr[17] == 1){
                cout << "The result of the print: " << register_arr[10] << endl;
            }
            else if(register_arr[17] == 10){
                // terminate the program
                exit(0);
            }
        }
        // else if (immediate_decimal == 1) //ebreak
        // {

        // }
        PC++;
    }   
}

// STYPE
void Stype(string opcode, string func3, int rs1_decimal, int rs2_decimal, int immediate_decimal)
{
    if (func3 == "000") //SB
    {
        string str = decimalToBinarySigned(register_arr[rs2_decimal]);  //SB
        cout << "str = " << str << endl;
        for(int i=0; i<24; i++)
        {
            if(str[24] == '1'){
                str[i] = '1';
            }
            else{
                str[i] = '0';
            }
        }

        cout << "str = " << str << endl;
        register_arr[rs2_decimal] = binaryToSignedDecimal(str);
        
        register_arr[rs1_decimal + immediate_decimal] = register_arr[rs2_decimal];  //SB
        cout << "sb x" << rs2_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
        cout << "The result of the store: " << register_arr[rs1_decimal + immediate_decimal] << endl;
    }
    else if (func3 == "001") //SH
    {
        string str = decimalToBinarySigned(register_arr[rs1_decimal + immediate_decimal]);  //SH

        cout << "str = " << str << endl;
        for(int i=0; i<16; i++)
        {
            if(str[16] == '1'){
                str[i] = '1';
            }
            else{
                str[i] = '0';
            }
        }
        cout << "str = " << str << endl;
        register_arr[rs2_decimal] = binaryToSignedDecimal(str);

        register_arr[rs1_decimal + immediate_decimal] = register_arr[rs2_decimal];  //SH
        cout << "sh x" << rs2_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
        cout << "The result of the store: " << register_arr[rs1_decimal + immediate_decimal] << endl;
    }
    else if (func3 == "010") //SW
    {
        register_arr[rs1_decimal + immediate_decimal] = register_arr[rs2_decimal];  //SW
        cout << "sw x" << rs2_decimal << ", " << immediate_decimal << "(x" << rs1_decimal << ")" << endl;
        cout << "The result of the store: " << register_arr[rs1_decimal + immediate_decimal] << endl;
    }
    PC++;
}

// BTYPE
void Btype(string opcode, string func3, int rs1_decimal, int rs2_decimal, int immediate_decimal)
{
    // BEQ
    if (func3 == "000") // func = 0
    {
        if (register_arr[rs1_decimal] == register_arr[rs2_decimal])
        {
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }
        cout << "beq x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
    // BNE
    else if (func3 == "001") // func3 = 1
    {
        if (register_arr[rs1_decimal] != register_arr[rs2_decimal])
        {
            //PC = (immediate_decimal >> 1);
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }
        cout << "bne x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
    // BLT
    else if (func3 == "100") // func3 = 4
    {
        if (register_arr[rs1_decimal] < register_arr[rs2_decimal])
        {
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }

        cout << "blt x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
    // BGE
    else if (func3 == "101") // func3 = 5
    {
        if (register_arr[rs1_decimal] >= register_arr[rs2_decimal])
        {
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }
        cout << "bge x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
    // BLTU
    else if (func3 == "110") // func3 = 6
    {
        //unsigned aspect?
        int rs1_value= binaryToUnsignedDecimal(decimalToBinaryUnsigned(register_arr[rs1_decimal]));
        int rs2_value = binaryToUnsignedDecimal(decimalToBinaryUnsigned(register_arr[rs2_decimal]));

        if (rs1_value < rs2_value)
        {
            //cout << "PC = " << PC << endl;
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }
        cout << "bltu x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
    // BGEU
    else if (func3 == "111") // func3 = 7
    {
        //unsigned aspect?
        int rs1_value= binaryToUnsignedDecimal(decimalToBinaryUnsigned(register_arr[rs1_decimal]));
        int rs2_value = binaryToUnsignedDecimal(decimalToBinaryUnsigned(register_arr[rs2_decimal]));

        if (rs1_value < rs2_value)
        {
            //cout << "PC = " << PC << endl;
            if (immediate_decimal % 2 == 0)
            {
                cout << "even address" << endl;
                PC = (immediate_decimal >> 1); 
            }
            else 
            {
                cout << "odd address" << endl;
                PC = (immediate_decimal >> 1) + 1;
            }
        }
        else{
            PC++;
        }
        cout << "bgeu x" << rs1_decimal << ", x" << rs2_decimal << ", " << PC << endl;
        cout << "The result of the branching: " << instruction_arr[PC] << endl;
    }
}

// UTYPE
void Utype(string opcode, int rd_decimal, string immediate)
{
    if (opcode == "0110111") //LUI
    {
        for(int i=20; i<32; i++){
            immediate[i] = 0;
        }
        int immediate_decimal = binaryToUnsignedDecimal(immediate);
        immediate_decimal = immediate_decimal << 12;
        register_arr[rd_decimal] = immediate_decimal;
        cout << "lui x" << rd_decimal << ", " << immediate_decimal << endl;
        cout << "The result of the load: " << register_arr[rd_decimal] << endl;
        PC++;
    }
    else if (opcode == "0010111") //AUIPC
    {
        // for(int i=20; i<32; i++){
        //     immediate[i] = 0;
        // }

        cout << "imm = " << immediate << endl;
        int immediate_decimal = binaryToUnsignedDecimal(immediate);
        immediate_decimal = immediate_decimal << 12;
        register_arr[rd_decimal] = PC + immediate_decimal;
        cout << "auipc x" << rd_decimal << ", " << immediate_decimal << endl;
        cout << "The result of the addition: " << register_arr[rd_decimal] << endl;
        PC++;
    }
}

// // UTYPE
// void Utype(string opcode, int rd_decimal, string immediate)
// {
//     // Ensure the immediate string has at least 32 bits by prepending zeros
//     while (immediate.length() < 32) {
//         immediate = "0" + immediate;
//     }

//     // Set the last 12 bits to '0'
//     for (int i = 20; i < 32; i++) {
//         immediate[i] = '0';
//     }

//     int immediate_decimal = binaryToUnsignedDecimal(immediate);
//     immediate_decimal = immediate_decimal << 12;

//     if (opcode == "0110111") // LUI
//     {
//         register_arr[rd_decimal] = immediate_decimal;
//         cout << "lui x" << rd_decimal << ", " << immediate_decimal << endl;
//         cout << "The result of the load: " << register_arr[rd_decimal] << endl;
//     }
//     else if (opcode == "0010111") // AUIPC
//     {
//         register_arr[rd_decimal] = PC + immediate_decimal;
//         cout << "auipc x" << rd_decimal << ", " << immediate_decimal << endl;
//         cout << "The result of the addition: " << register_arr[rd_decimal] << endl;
//     }

//     PC++;
// }

// JTYPE
void Jtype(string opcode, int rd_decimal, int immediate_decimal)
{
    if (opcode == "1101111") //JAL
    {
        register_arr[rd_decimal] = PC + 1;
        if (immediate_decimal % 2 == 0)
        {
            cout << "even address" << endl;
            PC = (immediate_decimal >> 2); 
        }
        else 
        {
            cout << "odd address" << endl;
            PC = (immediate_decimal >> 2) + 1;
        }
        cout << "jal x" << rd_decimal << ", " << PC << endl;
        cout << "The result of the jump: " << instruction_arr[PC] << endl;
    }
}

void instruction(string str, string opcode, char type)
{
    string func3 = "000";
    string rd = "00000";
    string rs1 = "00000";
    string rs2 = "00000";
    string func7 = "0000000";
    string immediate;
    int j;
    int rd_decimal = 0;
    int rs1_decimal = 0;
    int rs2_decimal = 0;
    int immediate_decimal = 0;
    
//R-type instruction format
    if (type == 'R') 
    {
        //getting rd
        j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            rd_decimal = binaryToDecimal(rd);
            j++;
        }
        cout << "rd = " << rd << endl;

        //getting func3
        j = 0;
        for (int i = 17 ; i < 20; i++) //getting func3 value
        {
            func3[j] = str[i];
            j++;
        }
        cout << "func3 = " << func3 << endl;

        //getting rs1
        j = 0;
        for (int i = 12 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            rs1_decimal = binaryToDecimal(rs1);
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
            rs2_decimal = binaryToDecimal(rs2);
            j++;
        }
        cout << "rs2 = " << rs2 << endl;

        //getting func7
        j = 0;
        for (int i = 0 ; i < 7; i++) //getting func3 value
        {
            func7[j] = str[i];
            j++;
        }
        cout << "func7 = " << func7 << endl;

        Rtype(opcode, rd_decimal, func3, rs1_decimal, rs2_decimal, func7);
    }
//I-type instruction format
    if (type == 'I') 
    {
        //getting rd
        j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            j++;
        }
        rd_decimal = binaryToDecimal(rd);
        cout << "rd = " << rd << endl;
        cout << "rd_decimal = " << rd_decimal << endl;

        //getting func3
        j = 0;
        for (int i = 17 ; i < 20; i++) //getting func3 value
        {
            func3[j] = str[i];
            j++;
        }
        cout << "func3 = " << func3 << endl;

        //getting rs1
        j = 0;
        for (int i = 12 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            rs1_decimal = binaryToDecimal(rs1);
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting immediate
        j = 0;
        string immediate = "000000000000";
        for (int i = 0 ; i < 12; i++) //getting func3 value
        {
            immediate[j] = str[i];
            immediate_decimal = binaryToSignedDecimal(immediate);
            j++;
        }
        cout << "Imm = " << immediate << endl;
        cout << "Imm = " << immediate_decimal << endl;
        // immediate = "00000000000000000000" + immediate;

        Itype(opcode, rd_decimal, func3, rs1_decimal, immediate_decimal, immediate);
    }

//S-type instruction format
    if (type == 'S') 
    {
        //getting imm1[4:0]
        j = 0;
        string imm1 = "00000";
        for (int i = 20 ; i < 25; i++) //getting imm1 value
        {
            imm1[j] = str[i];
            j++;
        }
        cout << "imm[4:0] = " << imm1 << endl;

        //getting func3
        j = 0;
        for (int i = 17 ; i < 20; i++) //getting func3 value
        {
            func3[j] = str[i];
            j++;
        }
        cout << "func3 = " << func3 << endl;

        //getting rs1
        j = 0;
        for (int i = 12 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            rs1_decimal = binaryToDecimal(rs1);
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
            rs2_decimal = binaryToDecimal(rs2);
            j++;
        }
        cout << "rs2 = " << rs2 << endl;

        //getting imm2[11:5]
        string imm2 = "0000000";
        j = 0;
        for (int i = 0 ; i < 7; i++) //getting imm2 value
        {
            imm2[j] = str[i];
            j++;
        }
        cout << "imm[11:5] = " << imm2 << endl;

        //combine the immediate values
        string immediate = imm2 + imm1;
        immediate_decimal = binaryToSignedDecimal(immediate);

        cout << "imm = " << immediate << endl;   

        Stype(opcode, func3, rs1_decimal, rs2_decimal, immediate_decimal);
    }

//B-type instruction format
    if (type == 'B') 
    {
        //getting imm1[4:1|11]
        int j = 0;
        string imm1 = "0";
        string imm2 = "0000";
        imm1[0] = str[24]; //imm[11]
        for (int i = 20 ; i < 24; i++) //getting imm1 value
        {
            imm2[j] = str[i];
            j++;
        }
        cout << "imm[11] = " << imm1 << endl;
        cout << "imm[4:1] = " << imm2 << endl;

        //getting func3
        j = 0;
        for (int i = 17 ; i < 20; i++) //getting func3 value
        {
            func3[j] = str[i];
            j++;
        }
        cout << "func3 = " << func3 << endl;

        //getting rs1
        j = 0;
        for (int i = 12 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            rs1_decimal = binaryToDecimal(rs1);
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
            rs2_decimal = binaryToDecimal(rs2);
            j++;
        }
        cout << "rs2 = " << rs2 << endl;

        //getting imm2[12|10:5]
        string imm3 = "000000";
        string imm4 = "0"; 
        imm4[0] = str[0]; //imm[12]
        for (int i = 1 ; i < 7; i++) //getting imm2 value
        {
            imm3[j] = str[i];
            j++;
        }
        cout << "imm[10:5] = " << imm3 << endl;
        cout << "imm[12] = " << imm4 << endl;

        immediate = imm4 + imm1 + imm3 + imm2 + '0';
        cout << "immediate = " << immediate << endl;
        immediate_decimal = binaryToDecimal(immediate);


        Btype(opcode, func3, rs1_decimal, rs2_decimal, immediate_decimal);
    }

//U-type instruction format
    if (type == 'U') 
    {
        int j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            j++;
        }
        cout << "rd = " << rd << endl;

        //getting imm2[12|10:5]
        j = 0;
        string immediate = "00000000000000000000000000000000";
        for (int i = 0 ; i < 20; i++) //getting imm2 value
        {
            immediate[j] = str[i];
            j++;
        }
        // cout << "imm[31:12] = " << immediate << endl;
        for (int i = 20; i < 32; i++)
        {
            immediate[i] = '0';
        }
        cout << "imm[31:12] = " << immediate << endl;
        rd_decimal = binaryToDecimal(rd);
        Utype(opcode, rd_decimal, immediate);
    }

//J-type instruction format
    if (type == 'J') 
    {
        int j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            j++;
        }
        cout << "rd = " << rd << endl;
        rd_decimal = binaryToDecimal(rd);

        //getting imm2[12|10:5]
        string immediate = "00000000000000000000";
        string imm3 = "00000000";
        j = 0;
        for (int i = 12 ; i < 20; i++) //getting imm3 value
        {
            imm3[j] = str[i];
            j++;
        }

        string imm2 = "0";
        imm2[0] = str[11];
        
        string imm1 = "0000000000";
        j = 0;
        for (int i = 1 ; i < 11; i++) //getting imm2 value
        {
            imm1[j] = str[i];
            j++;
        }

        string imm4 = "0";
        imm4[0] = str[0];

        immediate = imm4 + imm3 + imm2 + imm1 + '0' ;
        immediate_decimal = binaryToSignedDecimal(immediate);
        cout << "imm4" << imm4 << endl;
        cout << "imm3" << imm3 << endl;
        cout << "imm2" << imm2 << endl;
        cout << "imm1" << imm1 << endl;
        cout << "imm[20|10:1|11|19:12] = " << immediate << endl;

        Jtype(opcode, rd_decimal, immediate_decimal);
    }

}

void decode(string str)
{
    string opcode = "0000000"; // Initialize with 7 zeros
    char type;
    // string func3 = "000";
    // string rd = "00000";
    // string rs1 = "00000";
    // string rs2 = "00000";

    int j = 7;
    for (int i = str.size() ; i > str.size() - 8; i--) //getting opcode value
    {
        opcode[j] = str[i];
        j--;
    }

    //checking which type the opcode is refering to
    if (opcode == "0110011")
    {
        cout << "R-type" << endl;
        type = 'R';
        instruction(str, opcode, type);
    }
    else if (opcode == "0010011" || opcode == "0000011" || opcode == "1100111" || opcode == "1110011")
    {
        cout << "I-type" << endl;
        type = 'I';
        instruction(str, opcode, type);
    }
    else if (opcode == "0100011")
    {
        cout << "S-type" << endl;
        type = 'S';
        instruction(str, opcode, type);
    }
    else if (opcode == "1100011")
    {
        cout << "B-type" << endl;
        type = 'B';
        instruction(str, opcode, type);
    }
    else if (opcode == "1101111")
    {
        cout << "J-type" << endl;
        type = 'J';
        instruction(str, opcode, type);
    }
    else if (opcode == "0110111" || opcode == "0010111")
    {
        cout << "U-type" << endl;
        type = 'U';
        instruction(str, opcode, type);
    }
    else 
    {
        cout << "Error! Unknown instruction!" << endl;
    }


}




// Function to display an error message and terminate the program
void emitError(const string &message) {
    cerr << message << endl;
    exit(1);
}

void instDecExec(unsigned int instWord, ofstream &outfile) {
    // Placeholder function to simulate instruction decode and execute.
    // Replace this with your actual implementation.
    outfile << bitset<32>(instWord) << endl; // Write the 32-bit instruction to file
}

unsigned char memory[65536]; // Define memory size
int main(int argc, char *argv[]) {
    string str;
    int line_count = 0;
    int data_counter = 0;
    unsigned int instWord = 0;
    ifstream inFile;
    ofstream outFile;

    if (argc < 2) emitError("use: rvsim <input_instruction_file_name> [<input_data_file_name>]\n");

    inFile.open(argv[1], ios::in | ios::binary | ios::ate);
    if (inFile.is_open()) {
        int fsize = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        if (!inFile.read((char *)memory, fsize)) emitError("Cannot read from input file\n");

        outFile.open("machinecode.txt", ios::out | ios::trunc);
        if (!outFile.is_open()) emitError("Cannot open machinecode.txt for writing\n");

        while (PC < fsize) {
            instWord = (unsigned char)memory[PC] |
                       (((unsigned char)memory[PC + 1]) << 8) |
                       (((unsigned char)memory[PC + 2]) << 16) |
                       (((unsigned char)memory[PC + 3]) << 24);
            PC += 4;
            instDecExec(instWord, outFile);
        }

        outFile.close();
        inFile.close();
    } else {
        emitError("Cannot access input file\n");
    }

    if (argc == 3) {
        ifstream additionalFile(argv[2], ios::in | ios::binary | ios::ate);
        if (!additionalFile.is_open()) emitError("Cannot access additional binary file\n");

        int addFsize = additionalFile.tellg();
        additionalFile.seekg(0, additionalFile.beg);
        unsigned char *additionalMemory = new unsigned char[addFsize];

        if (!additionalFile.read((char *)additionalMemory, addFsize)) emitError("Cannot read from additional binary file\n");

        ofstream dataFile("data.txt", ios::out | ios::trunc);
        if (!dataFile.is_open()) emitError("Cannot open data.txt for writing\n");

        // Write binary content to data.txt
        for (int i = 0; i < addFsize; i += 4) {
            unsigned int instWord = (unsigned char)additionalMemory[i] |
                                    (((unsigned char)additionalMemory[i + 1]) << 8) |
                                    (((unsigned char)additionalMemory[i + 2]) << 16) |
                                    (((unsigned char)additionalMemory[i + 3]) << 24);
            dataFile << bitset<32>(instWord) << endl; // Convert to binary and write to data.txt
        }

        dataFile.close();
        additionalFile.close();
        delete[] additionalMemory;
    }

    ifstream file1("machinecode.txt");
    ifstream file2("data.txt");

    // Test values
    register_arr[1] = 2389577;
    register_arr[4] = 4;
    register_arr[3] = 2;
    register_arr[2] = 3;
    register_arr[9] = 3;
    register_arr[0] = 0;

    cout << endl;

    if (!file1.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }
    if (!file2.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    PC = 0;
    string line;
    // Read the file line by line
    while (getline(file1, line)) {
        instruction_arr[PC] = line;
        cout << line << endl;
        PC++;
        line_count++; // increment the line count
    }

    while (getline(file2, line)) {
        data_arr[data_counter] = line;
        cout << line << endl;
        data_counter++; // increment the data count
    }

    cout << "-----------------------------------------------------------------" << endl;
    PC = 0;
    while (PC < line_count) {
        cout << "PROGRAM COUNTER = " << PC << endl;
        cout << instruction_arr[PC] << endl;
        str = instruction_arr[PC];
        decode(str);
    }

    cout << "*****************************************************************" << endl;

    return 0;
}
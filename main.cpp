#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int data_arr[32];

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
            data_arr[rd_decimal] = data_arr[rs1_decimal] + data_arr[rs2_decimal];
            cout << "add x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
            cout << "The result of the addition: " << data_arr[rd_decimal] << endl;
        }
        else //SUB
        {
            data_arr[rd_decimal] = data_arr[rs1_decimal] - data_arr[rs2_decimal];
            cout << "The result of the addition: " << data_arr[rd_decimal] << endl;
        }
    }
    else if (func3 == "001") //func3 = 1
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] << data_arr[rs2_decimal];  //SLL
    }
    else if (func3 == "010") //func3 = 2
    {

        data_arr[rd_decimal] = data_arr[rs1_decimal] < data_arr[rs2_decimal];  //SLT
        cout << "slt x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the comparison: " << data_arr[rd_decimal] << endl;
    }
    else if (func3 == "011") //func3 = 3
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] < data_arr[rs2_decimal];  //SLTU
        cout << "sltu x" << rd_decimal << ", x" << rs1_decimal << ", x" << rs2_decimal << endl;
        cout << "The result of the comparison: " << data_arr[rd_decimal] << endl;
        // Need to add 0 extension
        
    }
    else if (func3 == "100") //func3 = 4
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] ^ data_arr[rs2_decimal];  //XOR
    }
    else if (func3 == "101") //func3 = 5
    {
        if (func7 == "0000000") //SRL
        {
            data_arr[rd_decimal] = data_arr[rs1_decimal] >> data_arr[rs2_decimal];
        }
        else //SRA
        {
            data_arr[rd_decimal] = data_arr[rs1_decimal] >> data_arr[rs2_decimal];
            // Need to add sign extension
        }
    }
    else if (func3 == "110") //func3 = 6
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] | data_arr[rs2_decimal];  //OR
    }
    else if (func3 == "111") //func3 = 7
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] & data_arr[rs2_decimal];  //AND
    }
}

// ITYPE
void Itype(string opcode, int rd_decimal, string func3, int rs1_decimal, int immediate_decimal)
{
    if (func3 == "000") //func3 = 0
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] + immediate_decimal;  //ADDI
        cout << "addi x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
        cout << "The result of the addition: " << data_arr[rd_decimal] << endl;
    }
    else if (func3 == "010") //func3 = 2
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] < immediate_decimal;  //SLTI
        cout << "slti x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
        cout << "The result of the comparison: " << data_arr[rd_decimal] << endl;
    }
    else if (func3 == "011") //func3 = 3
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] < immediate_decimal;  //SLTIU
        cout << "sltiu x" << rd_decimal << ", x" << rs1_decimal << ", " << immediate_decimal << endl;
        cout << "The result of the comparison: " << data_arr[rd_decimal] << endl;
        // Need to add 0 extension
    }
    else if (func3 == "100") //func3 = 4
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] ^ immediate_decimal;  //XORI
    }
    else if (func3 == "110") //func3 = 6
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] | immediate_decimal;  //ORI
    }
    else if (func3 == "111") //func3 = 7
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] & immediate_decimal;  //ANDI
    }
    else if (func3 == "001") //func3 = 1
    {
        data_arr[rd_decimal] = data_arr[rs1_decimal] << immediate_decimal;  //SLLI
    }
    else if (func3 == "101") //func3 = 5
    {
        if (opcode == "0010011") //SRLI
        {
            data_arr[rd_decimal] = data_arr[rs1_decimal] >> immediate_decimal;
        }
        else //SRAI
        {
            data_arr[rd_decimal] = data_arr[rs1_decimal] >> immediate_decimal;
            // Need to add sign extension
        }
    }   
}

void instruction(string str, string opcode, char type)
{
    string func3 = "000";
    string rd = "00000";
    string rs1 = "00000";
    string rs2 = "00000";
    string func7 = "0000000";
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

        Itype(opcode, rd_decimal, func3, rs1_decimal, immediate_decimal);
    }


    if (type == 'S') //S-type instruction format
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

        //Stype(opcode, imm1, func3, rs1, rs2, imm2);
    }

    if (type == 'B') //B-type instruction format
    {
        //getting imm1[4:1|11]
        int j = 0;
        string imm1 = "00000";
        for (int i = 20 ; i < 25; i++) //getting imm1 value
        {
            imm1[j] = str[i];
            j++;
        }
        cout << "imm[4:1|11] = " << imm1 << endl;

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
        string imm2 = "0000000";
        for (int i = 0 ; i < 7; i++) //getting imm2 value
        {
            imm2[j] = str[i];
            j++;
        }
        cout << "imm[12|10:5] = " << imm2 << endl;

        //Btype(opcode, imm1, func3, rs1, rs2, imm2);
    }

    if (type == 'U') //U-type instruction format
    {
        int j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            j++;
        }
        cout << "rd = " << rd << endl;

        //getting imm2[12|10:5]
        string immediate = "00000000000000000000";
        for (int i = 0 ; i < 20; i++) //getting imm2 value
        {
            immediate[j] = str[i];
            j++;
        }
        cout << "imm[31:12] = " << immediate << endl;

        //Utype(opcode, rd, immediate);
    }


    if (type == 'J') //J-type instruction format
    {
        int j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
            j++;
        }
        cout << "rd = " << rd << endl;

        //getting imm2[12|10:5]
        string immediate = "00000000000000000000";
        for (int i = 0 ; i < 20; i++) //getting imm2 value
        {
            immediate[j] = str[i];
            j++;
        }
        cout << "imm[20|10:1|11|19:12] = " << immediate << endl;

        //Jtype(opcode, rd, immediate);
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
        cout << "Error!" << endl;
    }


}

int main()
{
    string str;
    int line_count = 0;
    ifstream file("C:/Users/omars/OneDrive/Desktop/Uni/AUC/Summer 24/Assembly/Project 1/Assembly_Project1/machinecode.txt");
    string instruction_arr[100];

    // Test values
    data_arr[2] = 4;
    data_arr[3] = 1;
    data_arr[8] = 2;
    data_arr[9] = 3;
    data_arr[0] = 0;

    cout << endl;

    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    int i=0;
    // Read the file line by line
    while (getline(file, line)) {
        //cout << endl;
        instruction_arr[i] = line;
        cout << line << endl;
        i++;
        line_count++; // increment the line count
    }

    cout << "-----------------------------------------------------------------" << endl;

    for (int i=0; i<line_count; i++)
    {
        cout << instruction_arr[i] << endl;
        str=instruction_arr[i];
        decode(str);
        
    }

    //data_arr[18]=0;

    
    cout << "*****************************************************************" <<endl;
    // for(int i=0; i<str.size(); i++)
    // {
    //     cout << str[i] << endl;
    // }


    // Close the file
    file.close();

    return 0;
}
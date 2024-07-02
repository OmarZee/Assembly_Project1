#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void instruction(string str, string opcode, char type)
{
    string func3 = "000";
    string rd = "00000";
    string rs1 = "00000";
    string rs2 = "00000";
    string func7 = "0000000";
    int j;

    if (type == 'R') //R-type instruction format
    {
        //getting rd
        j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
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
        for (int i = 19 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
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

        //Rtype(opcode, rd, func3, rs1, rs2, func7);
    }

    if (type == 'I') //I-type instruction format
    {
        //getting rd
        j = 0;
        for (int i = 20 ; i < 25; i++) //getting rd value
        {
            rd[j] = str[i];
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
        for (int i = 19 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting immediate
        j = 0;
        string immediate = "0000000";
        for (int i = 0 ; i < 7; i++) //getting func3 value
        {
            immediate[j] = str[i];
            j++;
        }
        cout << "Imm = " << immediate << endl;

        //Itype(opcode, rd, func3, rs1, immediate);
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
        for (int i = 19 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
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
        for (int i = 19 ; i < 17; i++) //rs1 value
        {
            rs1[j] = str[i];
            j++;
        }
        cout << "rs1 = " << rs1 << endl;

        //getting rs2
        j = 0;
        for (int i = 7 ; i < 12; i++) //getting rs2 value
        {
            rs2[j] = str[i];
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
    ifstream file("machinecode.txt");
    string array[100];

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
        array[i] = line;
        cout << line << endl;
        i++;
    }

    cout << "-----------------------------------------------------------------" << endl;

    for (int i=0; i<100; i++)
    {
        cout << array[i] << endl;
        // for (int j=0; j<array[i].size(); j++)
        // {

        // }
        
        
    }
    string str;
    str=array[0];
    decode(str);
    cout << "*" <<endl;
    // for(int i=0; i<str.size(); i++)
    // {
    //     cout << str[i] << endl;
    // }


    // Close the file
    file.close();

    return 0;
}
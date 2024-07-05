#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

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
    unsigned int instWord = 0;
    ifstream inFile;
    ofstream outFile;
    unsigned int pc = 0; // Initialize program counter

    if (argc < 3) emitError("use: rvsim <input_file_name> <output_file_name>\n");

    inFile.open(argv[1], ios::in | ios::binary | ios::ate);
    if (inFile.is_open()) {
        int fsize = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        if (!inFile.read((char *)memory, fsize)) emitError("Cannot read from input file\n");

        outFile.open(argv[2], ios::out | ios::trunc);
        if (!outFile.is_open()) emitError("Cannot open output file\n");

        while (pc < fsize) {
            instWord = (unsigned char)memory[pc] |
                       (((unsigned char)memory[pc + 1]) << 8) |
                       (((unsigned char)memory[pc + 2]) << 16) |
                       (((unsigned char)memory[pc + 3]) << 24);
            pc += 4;
            instDecExec(instWord, outFile);
        }

        outFile.close();
        inFile.close();
    } else {
        emitError("Cannot access input file\n");
    }

    return 0;
}

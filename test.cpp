#include <iostream>
#include <fstream>

using namespace std;

// Assuming memory is defined somewhere in your program
unsigned char memory[4096]; // Adjust size as needed

void emitError(const string& msg) {
    cerr << msg << endl;
    exit(1);
}

void instDecExec(unsigned int instWord) {
    // Implementation of instruction decode and execute
    // This function needs to be implemented based on your RISC-V simulator
    // Example:
    cout << "Executing instruction: " << hex << instWord << endl;
}

int main(int argc, char *argv[]) {
    unsigned int instWord = 0;
    ifstream inFile;
    ofstream outFile;

    if (argc < 2) {
        emitError("use: rvcdiss <machine_code_file_name>\n");
    }

    inFile.open(argv[1], ios::in | ios::binary);
    if (inFile.is_open()) {
        // Read the entire file into memory
        inFile.read((char *)memory, sizeof(memory));

        // Calculate number of instructions
        int numInstructions = inFile.gcount() / 4;

        // Process each 32-bit instruction
        for (int i = 0; i < numInstructions; ++i) {
            instWord = (unsigned char)memory[i*4] |
                       (((unsigned char)memory[i*4+1]) << 8) |
                       (((unsigned char)memory[i*4+2]) << 16) |
                       (((unsigned char)memory[i*4+3]) << 24);

            // Execute the instruction
            instDecExec(instWord);
        }
    } else {
        emitError("Cannot access input file\n");
    }

    inFile.close();
    return 0;
}

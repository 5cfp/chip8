#include <cstdint>
#include <fstream>


// Define memory, registers, stack, and others
uint8_t V[16];
uint16_t memory[4096];
uint16_t Index;
uint16_t pc;
uint16_t stack[16];
uint8_t sp;
uint8_t delaytimer;
uint8_t soundtimer;
uint8_t keys[16];
uint32_t screen[64 * 32];
uint16_t opcode;

// Memory START_ADDRESS because Chip8 programes starts from this address
const unsigned int START_ADDRESS = 0x200;

// the start address of the fontset in chip8 memory
const unsigned int FONTSET_START_ADDRESS = 0x50;

// chip8 all 16 characters
const unsigned int FONTSET_SIZE = 80;

// characters sprites
uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


// a function to initilaize the emulator
void initilaize(){
    
    pc = START_ADDRESS; // Initialize pc from the start address
    opcode = 0; // Reset opcode
    Index = 0; // reset
    sp = 0; // reset

    // clear stack
    for (int i = 0; i < 16; ++i){
        stack[i] = 0;
    }
    
    // clear registors V0-VF
    for (int i = 0; i < 16; ++i){
        V[i] = 0;
    }

    // clear memory
    for (int i = 0; i < 4096; ++i){
        memory[i] = 0;
    }

    
    // Load fonts into memory from the start address of fontset in memory
	for (unsigned int i = 0; i < FONTSET_SIZE; ++i){
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}
}


// a function to load rom in the emulator memory
void loadrom(const char *filename){

    // Open the file as binary and move the file pointer to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open()){
        // get the rom file size and make a buffer to store binary rom data on it
        std::streampos size = file.tellg();
        char *buffer = new char[size];

        // go to the beginning of the file and fill the buffer and close the file after that
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // load the rom from the buffer to the emulator's memory from address 0x200
        for (int i = 0; i < size; ++i){
            memory[START_ADDRESS + i] = buffer[i];
        }

        // free the buffer
        delete[] buffer;
    }

}
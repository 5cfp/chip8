#include "chip8.hpp"

// random function
uint8_t randByte (uint8_t random){
        srand(static_cast<unsigned int>(time(0)));
        return random = rand();
}

// a function to initilaize the emulator
void initilaize(){

    std::cout << "Chip8 Emulator!!!" << std::endl;
    
    pc = START_ADDRESS; // Initialize pc from the start address
    opcode = 0; // Reset 
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

    else{
        std::cerr << "Feild to open file: " << filename << std::endl;
    }

}

void emulatecycle(){



    pc += 2;
}

void updateTimers(){

    // delay timer decrement every one cycle until zero. it will not go below zero because its unsigned int
    if (delaytimer > 0){
        --delaytimer;
    }

    // sound timer decrement every one cycle until zero if. if soundtimer == 1 it will beep. it will not go below zero because its unsigned int
    if (soundtimer > 0){
        if (soundtimer == 1){
            // beep
        }
        --soundtimer;
    }
}


/*
and now the moment you all been waiting for
1
2
3
===================The Instructions========================
*/


void OP_00E0(){
    // clear screen code
}

void OP_0EE(){
    pc = stack[sp];
    --sp;
}

void OP_1nnn(){
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

void OP_2nnn(){
    uint16_t address = opcode & 0x0FFFu;
    ++sp;
    stack[sp] = pc;
    pc = address;
}

void OP_3xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(V[x] == byte){
        pc += 2;
    }
}

void OP_4xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if(V[x] != byte){
        pc += 2;
    }
}

void OP_5xy0(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    if(V[x] == V[y]){
        pc += 2;
    }
}

void OP_6xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    V[x] = byte;
}

void OP_7xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    V[x] += byte;
}

void OP_8xy0(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    V[x] = V[y];
}

void OP_8xy1(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    V[x] |= V[y];
}

void OP_8xy2(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    V[x] &= V[y];
}

void OP_8xy3(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    V[x] ^= V[y];
}

void OP_8xy4(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    uint16_t sum = V[x] + V[y];

    if (sum > 255U){
        V[0xF] = 1;
    }
    else {
        V[0xF] = 0;
    }

    V[x] = sum & 0xFFu;
}

void OP_8xy5(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;

    if (V[x] > V[y]){
        V[0xF] = 1;
    }
    else {
        V[0xF] = 0;
    }

    V[x] -= V[y];
}
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


// 00E0 CLS: Clear the display.
void OP_00E0(){

}

// 00EE RET: Return from the subroutine.
void OP_0EE(){

}

// 1nnn JP: Jump to location nnn.
void OP_1nnn(){

}

// 2nnn CALL: Call subroutine at nnn.
void OP_2nnn(){

}

// 3xkk - SE Vx, byte: Skip next instruction if Vx = kk.
void OP_3xkk(){

}
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include "i_type.h"
#include "cpu.h"

typedef struct Label_struct {
    char *label;
    int value;
} Label;

uint8_t get_opcode(uint32_t word) {
    // here we will extract the opcode from the word
    // We know that this is the first 6 bits
    // we can do a right shift by 26
    return word >> 26;
}

void output_registers(CPU *cpu) {
    for (int i = 0; i < 32; ++i) {
        printf("%d: %d\n", i, cpu->regs[i]);
    }
}

int main(void) {
    // First step:
    // Read and tokenise the file
    //
    // Second step:
    // Go over and build the symbol table
    //
    // Third step:
    // encode the instructions into the cpu memory
    //
    // Fourth step:
    // Set the PC and run it.

    FILE *fptr = fopen("../main.asm", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fptr == NULL) {
        exit(EXIT_FAILURE);
    }

    // we will read it line by line
    // We keep track of a table of labels,
    Label labels[10];

    uint32_t address = 0x00400000;
    while ((read = getline(&line, &len, fptr)) != -1) {
        // This is the first pass.
        // This time, we are trying to build up that symbol table.
        // The way we do this is keeping track of the memory address
        // When we come across a label, we store in our symbol table, label -> address
        char *tok[16];

        bool inWord = false;

        for (char *c_ptr = line; c_ptr < &line[read]; ++c_ptr) {
            if (!isspace(*c_ptr) && !inWord) {
                inWord = true;
            } else if (isspace(*c_ptr) && inWord){
                inWord = false;
            }
        }
        // we know if the first element ends in a colon, it will be a label
    }

    free(line);


    CPU cpu = init_cpu();
    cpu.mem[0] = 0x3C08000A; // addi $t0, $zero, 10

    // Loop over the instructions, with the same reference to the CPU
    // Instructions will be in the memory, which the PC then offsets
    while (cpu.pc < 1) {
        uint32_t instruction = cpu.mem[cpu.pc];

        uint8_t opcode = get_opcode(instruction);

        if (opcode == 0x00) { // R-Type
            printf("R-Type");
        } else if (opcode == 0x02 || opcode == 0x03) { // J-Type
            printf("J-Type");
        } else { // I-Type
            // Generic
            switch (opcode) {
                case 0x8:
                    if (!addi(&cpu, instruction)) {
                        printf("Error occurred.");
                    }
                    break;
                case 0x9:
                    if (!addiu(&cpu, instruction)) {
                        printf("Error occurred.");
                    }
                    break;
                case 0xC:
                    if (!andi(&cpu, instruction)) {
                        printf("Error occurred.");
                    }
                    break;
                case 0xF:
                    if (!lui(&cpu, instruction)) {
                        printf("Error occurred.");
                    }
                    break;
                default:
                    perror("Something went wrong.");
                    break;
            }
        }

        // we increment the program counter in the function, as some do it differently!
    }

    // output_registers(&cpu);
    return 0;
}

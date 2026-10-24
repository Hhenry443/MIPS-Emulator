#include <stdint.h>
#include <stdio.h>
#include "i_type.h"
#include "cpu.h"

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
    CPU cpu = init_cpu();

    cpu.regs[8] = 13;

    uint32_t word_1 = 0x3109000c;

    uint8_t opcode = get_opcode(word_1);


    // First step is to figure out the instruction type from the opcode.

    if (opcode == 0x00) { // R-Type
        printf("R-Type");
    } else if (opcode == 0x02 || opcode == 0x03) { // J-Type
        printf("J-Type");
    } else { // I-Type
        // Generic
        switch (opcode) {
            case 0x8:
                if (!addi(&cpu, word_1)) {
                    printf("Error occurred.");
                }
                break;
            case 0x9:
                if (!addiu(&cpu, word_1)) {
                    printf("Error occurred.");
                }
                break;
            case 0xC:
                if (!andi(&cpu, word_1)) {
                    printf("Error occurred.");
                }
                break;
            default:
                perror("Something went wrong.");
                break;
        }
    }

    output_registers(&cpu);
    return 0;
}

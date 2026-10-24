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

    output_registers(&cpu);
    return 0;
}

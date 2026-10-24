//
// Created by henry on 23/10/2026.
//

#include "i_type.h"

#include <stdio.h>

/*
 * This is a helper function to get the rs, rt and immediate from a uint32_t word
 * Uses bit shifts and a mask to get the right values.
 */
Fields disassemble_word(uint32_t word) {
    Fields f = {
        .rs = (word >> 21) & 0x1F,
        .rt = (word >> 16) & 0x1F,
        .immediate = word & 0xFFFF
    };

    return f;
}

/*
 * Sign extend a 16 bit integer to 32 bits.
 *
 * This will add 1's if the sign bit is 1 and 0 if the sign bit is 0
 */
int32_t sign_extend(uint32_t imm) {
    return (uint32_t)(int32_t)(int16_t)(imm & 0xFFFF);
}

/*
 * addi - Add Immediate
 *
 * Adds a signed 16 bit constant (immediate) to the contents of a source register
 * and stores the resulting sum in a target register
 *
 * Does not allow integer overflow, and will error if it encounters an overflow
 */
bool addi(CPU *cpu, uint32_t word) {
    Fields f = disassemble_word(word);

    // If we add them and the MSB is 1, then we know an overflow has occurred
    if (!!(f.immediate + cpu->regs[f.rs] & 0x80000000)) {
        return false;
    } else {
        // If not, complete the addition.
        cpu->regs[f.rt] = cpu->regs[f.rs] + f.immediate;
        return true;
    }
}

/*
 * addiu - Add Immediate Unsigned
 *
 * This adds an immediate value to a register without triggering an overflow exception
 *
 * Uses sign extension to turn the 16 bit immediate into a 32 bit integer
 */
bool addiu(CPU *cpu, uint32_t word) {
    Fields f = disassemble_word(word);

    // If not, complete the addition.
    cpu->regs[f.rt] = cpu->regs[f.rs] + sign_extend(f.immediate);
    return true;
}

/*
 * andi - Bitwise AND Immediate
 *
 * Performs a bitwise AND operation between a source register value and a 16 bit immediate.
 *
 * The result is stored in the destination register
 */
bool andi(CPU *cpu, uint32_t word) {
    // This one isn't too hard
    Fields f = disassemble_word(word);

    // Insert
    cpu->regs[f.rt] = cpu->regs[f.rs] & f.immediate;
}

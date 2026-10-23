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

int16_t sign_extend(uint16_t imm) {
    int ext_imm = imm & 0xFFFF;

    if (ext_imm & 0x80000000) {
        // if negative, append leading 1's to the og value
        ext_imm = ext_imm | 0xFFFF0000;
    }

    return (int16_t) ext_imm;
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
 * addiu -
 */
bool addiu(CPU *cpu, uint32_t word) {
    Fields f = disassemble_word(word);

    // If not, complete the addition.
    cpu->regs[f.rt] = cpu->regs[f.rs] + sign_extend(f.immediate);
    return true;
};


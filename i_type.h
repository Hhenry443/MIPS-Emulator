//
// Created by henry on 23/10/2026.
//

#ifndef MIPS_EMULATOR_R_TYPE_H
#define MIPS_EMULATOR_R_TYPE_H
#include <stdbool.h>
#include <stdint.h>
#include "cpu.h"

typedef struct Fields_Struct {
    uint32_t rs; // Source register
    uint32_t rt; // Target register
    int16_t immediate;
} Fields;

Fields disassemble_word(uint32_t word);

int32_t sign_extend(uint32_t imm);

bool addi(CPU *cpu, uint32_t word);

bool addiu(CPU *cpu, uint32_t word);

bool andi(CPU *cpu, uint32_t word);

bool lui(CPU *cpu, uint32_t word);

#endif //MIPS_EMULATOR_R_TYPE_H

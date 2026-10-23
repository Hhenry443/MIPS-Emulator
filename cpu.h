//
// Created by henry on 23/10/2026.
//

#ifndef MIPS_EMULATOR_CPU_H
#define MIPS_EMULATOR_CPU_H
#include <stdint.h>
#include <stdlib.h>

typedef struct CPU_Struct {
    uint32_t regs[32];
    uint32_t pc;
    uint8_t mem[4096];
} CPU;

CPU init_cpu();
#endif //MIPS_EMULATOR_CPU_H

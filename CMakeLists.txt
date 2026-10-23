cmake_minimum_required(VERSION 4.3)
project(MIPS_Emulator C)

set(CMAKE_C_STANDARD 11)

add_executable(MIPS_Emulator main.c
        i_type.c
        i_type.h
        cpu.c
        cpu.h)

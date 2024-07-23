cmake_minimum_required(VERSION 3.28)
project(EmuPDP_11 C)

set(CMAKE_C_STANDARD 11)

add_executable(EmuPDP_11
        src/pdp11_mem.c
        src/pdp.h
        src/pdp11.c
        src/pdp11_command.c
        src/logger.c
        src/pdp11_run.c)
add_executable(prim primitive.c)
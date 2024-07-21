cmake_minimum_required(VERSION 3.28)
project(EmuPDP_11 C)

set(CMAKE_C_STANDARD 11)

add_executable(EmuPDP_11
        pdp11_mem.c)
add_executable(prim primitive.c)
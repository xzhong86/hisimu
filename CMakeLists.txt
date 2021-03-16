
cmake_minimum_required(VERSION 3.10)
project(hisimu)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

file(GLOB base_srcs base/elf-loader/*Loader.cc base/mem-image/Mem*.cc)

file(GLOB arch_srcs arch/riscv/*.cc arch/riscv/gen/*.c)

add_executable(hisimu ${base_srcs} ${arch_srcs} sim/main.cc)


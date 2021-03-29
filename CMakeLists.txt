
cmake_minimum_required(VERSION 3.10)
project(hisimu)

set(CMAKE_C_COMPILER   clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-O3)

include_directories(.)

file(GLOB base_srcs
  base/elf-loader/*Loader.cc
  base/mem-image/Mem*.cc)
add_library(base ${base_srcs})


file(GLOB arch_riscv_srcs
  arch/riscv/*.cc
  arch/riscv/gen/*.c)
add_library(riscv ${arch_riscv_srcs})


add_executable(hisimu sim/main.cc)
target_link_libraries(hisimu base riscv)

add_subdirectory(test/riscv/utest)


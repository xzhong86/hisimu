# HiSimu Project

High-Speed Simulator.

## Requirements

 * CMake 3.10
 * racc, install with `gem install racc`
 * riscv toolchain, for compiling test case.


## Build

update submodule:
  `git submodule update --init --recursive`

build simple simulator:
  `mkdir build/ ; cd build/ ; cmake .. ; make`


## Speed Track

 * v1.0, pass hello test. 5 MIPS on server, 4.5 MIPS on MacBookPro-13.3-2018
 * v1.1, add -O3 flags, use clang.
   * Machine: MacBook Air 2020, Apple M1 SOC
   * Compiler: Apple clang version 12.0.0
   * Output format: Mach-O 64-bit executable arm64
   * Speed: 69 MIPS on hello-asm, 45 MIPS on array.


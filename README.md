# HiSimu Project

High-Speed Simulator.

## Requirements

 * CMake 3.10
 * ruby, ruby-dev (to install racc)
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
   * ----
   * Machine: Intel(R) Xeon(R) Platinum 8158 CPU @ 3.00GHz
   * Compiler: clang 6.0 on Ubuntu 18.04, with options '-O3 -march=native'
   * Speed: 59.5 MIPS on hello. 50.7 MIPS on 'array', 39 MIPS without -march=native
   * ----
   * Machine: Intel(R) Xeon(R) CPU E5-2680 v3 @ 2.50GHz
   * Compiler: clang 10.0 on Ubuntu 20.4, '-O3 -march=native'
   * Speed: 50 MIPS on hello. 41.7 MIPS on array.


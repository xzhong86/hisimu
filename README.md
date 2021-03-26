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



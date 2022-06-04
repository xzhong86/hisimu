# HiSimu Project

High-Speed Simulator with document style code for instruction behavior, see the code in arch/riscv/isa-def/.
高速文档式行为模型，目标是拥有文档一般的可读性和翻译执行的速度，目标速度500+MIPS。

Code example:
```c
INST_CLASS(i_type, <12.imm11_0><5.rs1><3.funct3><5.rd><7.opcode>) {
    DECODE() {
        simm32 = SIGN_EXT(imm11_0, 11);
    }
    DISASM() {
        ASM_FORMAT("[inst] [rd], [rs1], %d", simm32);
    }
}

INST(addi, <12.imm12><5.rs1>000<5.rd>0010011) {
    EXECUTE() {
        GPR[rd] = GPR[rs1] + simm32;
    }
}
```

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
 * v1.1, on Apple M1: 69 MIPS on hello-asm test, 45 MIPS on array test.

More speed details in [speed.md](speed.md)


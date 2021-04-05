
#include "rv64-cpu.h"
#include <string.h>
#include <stdio.h>

extern void riscv_decode_exec_inst(CPUState *cpu, uint32_t code);

void riscv_memory_access(CPUState *cpu, int type, uint64_t addr, void *buf, int size)
{
    memset(buf, 0, size);
}

int main()
{
    CPUState cpu;
    for (int i = 0; i < 32; i++)
        cpu.gpr[i] = 0;
    cpu.pc = 0;

    // INST(addi, <12.imm12><5.rs1>000<5.rd>0010011)
    riscv_decode_exec_inst(&cpu, 0x00500093);

    printf("GPR[1]=%ld\n", cpu.gpr[1]);
}

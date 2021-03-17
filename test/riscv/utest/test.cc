
#include <arch/riscv/cpu.h>
#include <string.h>
#include <stdio.h>

using namespace riscv;

extern "C" void riscv_decode_exec_inst(CPUState *cpu, uint32_t code);

void sanity_test(CPU *_cpu)
{
    CPUState *cpu = _cpu->getCPU();
    cpu->gpr[1] = 0;

    // addi x1, x1, 5
    // INST(addi, <12.imm12><5.rs1>000<5.rd>0010011)
    riscv_decode_exec_inst(cpu, 0x00500093);

    //test(cpu->gpr[1], 5);
    printf("GPR[1]=%ld\n", cpu->gpr[1]);
}

int main()
{
    CPU *cpu = new CPU();
    sanity_test(cpu);
}


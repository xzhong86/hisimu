
#include <arch/riscv/cpu.h>
#include <string.h>
#include <stdio.h>

#include <utils/utest/utest.h>

using namespace riscv;

extern "C" void riscv_decode_exec_inst(CPUState *cpu, uint32_t code);

struct RiscvCPU {
    CPU *cpu;
};

#define UTCPU (utest_fixture->cpu)

UTEST_F_SETUP(RiscvCPU) {
    UTCPU = new CPU();
}
UTEST_F_TEARDOWN(RiscvCPU) {
    delete UTCPU;
}
UTEST_F(RiscvCPU, addi) {
    CPUState *cpu = UTCPU->getCPU();
    cpu->gpr[1] = 0;
    // addi x1, x1, 5
    // INST(addi, <12.imm12><5.rs1>000<5.rd>0010011)
    riscv_decode_exec_inst(cpu, 0x00500093);
    ASSERT_EQ(5, cpu->gpr[1]);
}



#if 0
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
#endif


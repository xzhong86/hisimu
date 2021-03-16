
#include "cpu.h"

using namespace riscv;

static CPU *g_riscv_cpu_map[128];

uint32_t CPU::global_id_ = 0;

CPU::CPU()
{
    cpu_.cpu_id = global_id_ ++;
    g_riscv_cpu_map[cpu_.cpu_id] = this;

    // tbd: add reset method
    for (auto &reg: cpu_.gpr)
        reg = 0;
    cpu_.pc = 0;
    cpu_.csr = nullptr;
}

extern "C" void riscv_decode_exec_inst(CPUState *cpu, uint32_t code);

void CPU::step(int n)
{
    while (n-- > 0) {
        uint64_t pc = cpu_.pc;
        uint32_t inst;
        getCB().fetchInst(this, pc, &inst);
        if (getCB().beforeExecInst)
            getCB().beforeExecInst(this, inst);

        riscv_decode_exec_inst(&cpu_, inst);

        if (getCB().afterExecInst)
            getCB().afterExecInst(this, inst);
    }
}

//#include "isa-helper.h"
#define Load  1
#define Store 2

extern "C"
void riscv_memory_access(CPUState *_cpu, int type, uint64_t addr, void *buf, int size)
{
    CPU *cpu = g_riscv_cpu_map[_cpu->cpu_id];
    if (type == Load)
        cpu->getCB().readMemory(cpu, addr, buf, size);
    else if (type == Store)
        cpu->getCB().readMemory(cpu, addr, buf, size);
}

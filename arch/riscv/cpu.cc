
#include "cpu.h"

using namespace riscv;

static CPU *g_riscv_cpu_map[128];
static uint32_t g_riscv_cpu_id = 0;

CPU::CPU()
{
    rv_cpu_id_ = g_riscv_cpu_id ++;
    g_riscv_cpu_map[rv_cpu_id_] = this;
}

CPU * CPU::getCPU(unsigned rv_id) {
    return g_riscv_cpu_map[rv_id];
}


#define Load  1
#define Store 2

extern "C"
void riscv_memory_access(unsigned id, int type, uint64_t addr, void *buf, int size)
{
    CPU *cpu = CPU::getCPU(id);
    if (type == Load)
        cpu->getCB().readMemory(cpu, addr, buf, size);
    else if (type == Store)
        cpu->getCB().writeMemory(cpu, addr, buf, size);
}


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


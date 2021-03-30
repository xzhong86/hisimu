
#include "rv64-cpu.h"
#include "cpu-temp.h"

extern "C" void riscv_decode_exec_inst(CPUState *cpu, uint32_t code);

using namespace riscv;

namespace riscv {

struct RV64CPU : public CPUState {
    void decode_exec(uint32_t code) {
        riscv_decode_exec_inst(this, code);
    }
};

}

namespace arch {

template <>
GenericCPU * createGenericCPU<RV64CPU>()
{
    return new TemplCPU<RV64CPU>();
}

}


#define Load  1
#define Store 2

extern "C"
void riscv_memory_access(CPUState *_cpu, int type, uint64_t addr, void *buf, int size)
{
    riscv::CPU *cpu = riscv::CPU::getCPU(_cpu->cpu_id);
    if (type == Load)
        cpu->getCB().readMemory(cpu, addr, buf, size);
    else if (type == Store)
        cpu->getCB().readMemory(cpu, addr, buf, size);
}

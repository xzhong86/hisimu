
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

} // namespace riscv

namespace arch {

template <>
GenericCPU * createGenericCPU<RV64CPU>()
{
    return new TemplCPU<RV64CPU>();
}

} // namespace arch


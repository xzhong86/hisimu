// -*- C++ -*-
// internal template file

#pragma once

#include "cpu.h"

namespace riscv {

template <class RV_CPU>
class TemplCPU : public arch::GenericCPU {
    RV_CPU cpu_;
public:
    TemplCPU() {
        for (auto &reg: cpu_.gpr)
            reg = 0;
        cpu_.pc = 0;
        cpu_.csr = nullptr;
    }

    RV_CPU *getCPU()        { return &cpu_; }

    void setPC(uint64_t pc) override { cpu_.pc = pc; }
    uint64_t getPC() const  override { return cpu_.pc; }

    void setGPR(unsigned i, uint64_t v) override { cpu_.gpr[i] = v; }
    uint64_t getGPR(unsigned i)  const  override { return cpu_.gpr[i]; }

    void executeInst(uint64_t _inst) override {
	uint32_t inst = _inst;
	cpu_.decode_exec(inst);
    }
    void step(int n) override {
        while (n-- > 0) {
            uint64_t pc = cpu_.pc;
            uint32_t inst;
            getCB().fetchInst(this, pc, &inst);
            if (getCB().beforeExecInst)
                getCB().beforeExecInst(this, inst);

            cpu_.decode_exec(inst);

            if (getCB().afterExecInst)
                getCB().afterExecInst(this, inst);

            if (cpu_.pc == pc)
                cpu_.pc += 4;
        }
    }
};

}

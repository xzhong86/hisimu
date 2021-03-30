// -*- C++ -*-

#pragma once

#include <arch/generic/cpu.h>

namespace riscv {

class CPU : public arch::GenericCPU {
    unsigned rv_cpu_id_;
public:
    CPU();

    //======== common methods for RSIC-V 32bit and 64 bit cpu

    static CPU * getCPU(unsigned rv_id); // get CPU by ID

};


class RV32CPU;
class RV64CPU;

// create risc-v cpu like:
// auto *cpu createGenericCPU<riscv::RV64CPU>();

} // namespace riscv


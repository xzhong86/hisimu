
#ifndef __RISCV_RV64_CPU_H__
#define __RISCV_RV64_CPU_H__

#ifdef __RISCV_RV32_CPU_H__
#error "Both rv32-cpu.h and rv64-cpu.h are included"
#endif

#include <stdint.h>

#define RISCV64_CPU 1

#define XLEN 64

typedef int64_t  signed_reg_t;
typedef uint64_t unsigned_reg_t;
typedef uint64_t reg_t;

struct CPUState64 {
    reg_t gpr[32];
    reg_t pc;

    struct CPUCSR *csr;

    uint32_t cpu_id;
};
typedef struct CPUState64 CPUState64;

#define CPUState CPUState64

#endif //__RISCV_RV64_CPU_H__


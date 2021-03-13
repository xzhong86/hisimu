// -*- C++ -*-

#pragma once

#include <stdint.h>

#ifdef __cplusplus__
namespace arch {
#endif

typedef int64_t  signed_reg_t;
typedef uint64_t unsigned_reg_t;
typedef uint64_t reg_t;

struct CPUState {
    reg_t gpr[32];
    reg_t pc;

    struct CPUCSR *csr;
};
typedef struct CPUState CPUState;

#ifdef __cplusplus__
}
#endif


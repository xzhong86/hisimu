
#pragma once

#ifdef __cplusplus
#error "Could NOT include isa-helper.h in C++ project"
#endif

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define CPU   cpu
#define GPR   (cpu->gpr)
#define PC    (cpu->pc)

#define EXTRACT_BITS(bin, pos, len) ( ((bin) >> pos) & ((1UL << len) - 1) )
#define SIGN_EXT(bin, pos)  ( ((long long)((bin) << (31 - (pos)))) >> (31 - (pos)) )


#define JUMP_TO(PC)  do { cpu->pc = (PC); } while (0)

#define Load  1
#define Store 2
extern void riscv_memory_access(CPUState *cpu, int type, uint64_t addr, void *buf, int size);

#define MemoryAccess(type, addr, buf, size) do {                        \
        riscv_memory_access(cpu, (type), (addr), (buf), (size));        \
    } while (0)


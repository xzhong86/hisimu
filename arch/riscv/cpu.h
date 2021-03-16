// -*- C++ -*-

#pragma once

#include <stdint.h>

#ifdef __cplusplus
namespace riscv {
#endif

typedef int64_t  signed_reg_t;
typedef uint64_t unsigned_reg_t;
typedef uint64_t reg_t;

struct CPUState {
    reg_t gpr[32];
    reg_t pc;

    struct CPUCSR *csr;

    uint32_t cpu_id;
};
typedef struct CPUState CPUState;


#ifdef __cplusplus
} // namespace riscv

//#include <typeinfo> // g++ bug?
#include <functional>

namespace riscv {

class CPU {
    static uint32_t global_id_;
    CPUState cpu_;
public:
    CPU();
    CPUState *getCPUState() { return &cpu_; }
    void setPC(uint64_t pc) { cpu_.pc = pc; }
    uint64_t getPC() const  { return cpu_.pc; }

    void step(int n); // execute n instructions
    //void run();       // run unlimited

    struct CallBack {
        std::function<void(CPU*,uint32_t)> beforeExecInst;
        std::function<void(CPU*,uint32_t)> afterExecInst;
        std::function<void(CPU*,uint64_t,uint32_t*)> fetchInst;
        std::function<void(CPU*,uint64_t,void*,int)> readMemory;
        std::function<void(CPU*,uint64_t,void*,int)> writeMemory;
    };
    void setCallBack(const CallBack &cb) { cpu_cb_ = cb; }
    const CallBack &getCB() const { return cpu_cb_; }

private:
    CallBack cpu_cb_;
};

} // namespace riscv
#endif // __cplusplus


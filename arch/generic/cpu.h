// -*- C++ -*-

#pragma once

#include <stdint.h>
#include <functional>

namespace arch {

class GenericCPU {
public:
    GenericCPU();
    virtual ~GenericCPU() { }

    unsigned getID() const { return cpu_id_; }

    virtual void setPC(uint64_t pc) = 0;
    virtual uint64_t getPC() const  = 0;

    virtual void setGPR(unsigned, uint64_t);
    virtual uint64_t getGPR(unsigned) const;

    virtual void executeInst(uint64_t inst) = 0;
    virtual void step(int n); // execute n instructions
    virtual void run();       // run unlimited

    struct CallBack {
        std::function<void(GenericCPU*,uint32_t)> beforeExecInst;
        std::function<void(GenericCPU*,uint32_t)> afterExecInst;
        std::function<void(GenericCPU*,uint64_t,uint32_t*)> fetchInst;
        std::function<void(GenericCPU*,uint64_t,void*,int)> readMemory;
        std::function<void(GenericCPU*,uint64_t,void*,int)> writeMemory;
    };
    void setCallBack(const CallBack &cb) { cpu_cb_ = cb; }
    const CallBack &getCB() const { return cpu_cb_; }

private:
    CallBack cpu_cb_;
    unsigned cpu_id_;
};

template <class T>
GenericCPU * createGenericCPU();

} // namespace


#include "cpu.h"

using namespace arch;

static unsigned global_cpu_id = 0;

GenericCPU::GenericCPU() {
    cpu_id_ = global_cpu_id ++;
}

void GenericCPU::setGPR(unsigned, uint64_t) { }
uint64_t GenericCPU::getGPR(unsigned) const { return 0; }

void GenericCPU::step(int n) {
    while (n-- > 0) {
	uint64_t pc = getPC();
	uint32_t inst;
	getCB().fetchInst(this, pc, &inst);
	if (getCB().beforeExecInst)
	    getCB().beforeExecInst(this, inst);

	executeInst(inst);

	if (getCB().afterExecInst)
	    getCB().afterExecInst(this, inst);

	if (getPC() == pc)
	    setPC(pc + 4);
    }
}

void GenericCPU::run() {
    while (1) {
	step(1000000);
    }
}


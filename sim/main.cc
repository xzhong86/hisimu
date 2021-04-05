
#include <arch/riscv/cpu.h>
#include <base/ExeLoader.h>
#include <base/MemImage.h>

#include <iostream>
#include <cstdio>

using namespace base;
using namespace arch;
using std::printf;

using prop_t = ExeLoader::prop_t;

static const char *gpr_names[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0",   "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6",   "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8",   "s9", "s10","s11","t3", "t4", "t5", "t6"
};

class SimpleSimulator {
    MemImage *mim;
    ExeLoader *loader;
    GenericCPU *cpu;
    bool sim_debug = false;
    long num_inst = 0;

    void loadExecutable(const char *fname) {
	loader = createExeLoader(fname);
	if (!loader) {
	    std::cout << "Load ELF file '" << fname << "' failed.\n";
	    exit(1);
	}

	ExeLoader::CallBack ld_cb;
	ld_cb.loadData = [this](uint64_t pa, void* data, uint32_t size, prop_t){
	    mim->writeMem(pa, data, size);
	};
	ld_cb.setZero = [this](uint64_t pa, uint32_t size, prop_t){
	    mim->clear(pa, size);
	};

	loader->setCallBack(ld_cb);
	loader->loadFile();
    }
    void setupCPU() {
	cpu = createGenericCPU<riscv::RV64CPU>();
	num_inst = 0;
	sim_debug = false;

	GenericCPU::CallBack cpu_cb;

	cpu_cb.fetchInst = [this](GenericCPU*,uint64_t pc,uint32_t *pinst) {
	    mim->readMem(pc, pinst, sizeof(*pinst));
	};
	cpu_cb.readMemory = [this](GenericCPU*,uint64_t pa,void *buf,int size) {
	    mim->readMem(pa, buf, size);
	};
	cpu_cb.writeMemory = [this](GenericCPU *c,uint64_t pa,void *buf,int size) {
	    uint64_t watch_addr = 0x4034;
	    if (sim_debug && watch_addr >= pa && watch_addr < pa + size)
		printf("%lx: write to %lx\n", c->getPC(), pa);
	    mim->writeMem(pa, buf, size);
	};

	if (sim_debug) {
	    cpu_cb.beforeExecInst = [this](GenericCPU *cpu, uint32_t inst) {
		num_inst ++;
		if (num_inst < 20)
		    printf("%ld: exec PC=%lx, inst=%08x", num_inst, cpu->getPC(), inst);
	    };
	    cpu_cb.afterExecInst = [this](GenericCPU *cpu, uint32_t inst) {
		if (num_inst < 20)
		    dumpCPU();
	    };
	}
	cpu->setCallBack(cpu_cb);
    }
    void dumpCPU() {
	printf("%ld: %08lx:\n", num_inst, cpu->getPC());
	for (int r = 0; r < 32; ) {
	    for (int j = 0; j < 4; j++) {
		printf("%4s:%016lx ", gpr_names[r], cpu->getGPR(r));
                r++;
            }
	    printf("\n");
	}
    }
public:
    SimpleSimulator(const char *file) {
	mim = createMemImage("simple");
	loadExecutable(file);
	setupCPU();
    }
    void run() {
	std::cout << "Start simulation with PC=" << std::hex << loader->getEntryPoint()
		  << std::dec << std::endl;
	cpu->setPC(loader->getEntryPoint());
	int ninsts = 100 * 1000 * 1000;
	cpu->step(ninsts);
	std::cout << ninsts << " (" << ninsts / 1000000 << "M) Insts simulated.\n";
    }
};

int main(int argc, const char *argv[])
{
    // hello.elf is compiled from test/riscv/hello-asm
    const char *fname = "hello.elf";
    if (argc > 1)
	fname = argv[1];

    SimpleSimulator *sim = new SimpleSimulator(fname);
    sim->run();
}

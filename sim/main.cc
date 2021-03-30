
#include <arch/riscv/cpu.h>
#include <base/ExeLoader.h>
#include <base/MemImage.h>

#include <iostream>

using namespace base;
using namespace arch;

using prop_t = ExeLoader::prop_t;

int main(int argc, const char *argv[])
{
    MemImage *mim = createMemImage("simple");

    // hello.elf is compiled from test/riscv/hello-asm
    const char *fname = "hello.elf";
    if (argc > 1)
	fname = argv[1];
    ExeLoader *loader = createExeLoader(fname);
    if (!loader) {
	std::cout << "Load ELF file '" << fname << "' failed.\n";
	return 1;
    }

    ExeLoader::CallBack ld_cb;
    ld_cb.loadData = [mim](uint64_t pa, void* data, uint32_t size, prop_t){
        mim->writeMem(pa, data, size);
    };
    ld_cb.setZero = [mim](uint64_t pa, uint32_t size, prop_t){
        mim->clear(pa, size);
    };
    loader->setCallBack(ld_cb);

    loader->loadFile();

    GenericCPU *cpu = createGenericCPU<riscv::RV64CPU>();
    GenericCPU::CallBack cpu_cb;

    cpu_cb.fetchInst = [mim](GenericCPU*,uint64_t pc,uint32_t *pinst) {
        mim->readMem(pc, pinst, sizeof(*pinst));
    };
    cpu_cb.readMemory = [mim](GenericCPU*,uint64_t pa,void *buf,int size) {
        mim->readMem(pa, buf, size);
    };
    cpu_cb.writeMemory = [mim](GenericCPU*,uint64_t pa,void *buf,int size) {
        mim->writeMem(pa, buf, size);
    };

    long num_inst = 0;
    bool debug = false;
    if (debug) {
	cpu_cb.beforeExecInst = [&num_inst](GenericCPU *cpu, uint32_t inst) {
	    num_inst ++;
	    std::cout << num_inst << ": exec PC=" << std::hex << cpu->getPC()
		      << ", inst=" << inst << std::dec << std::endl;
	};
    }
    cpu->setCallBack(cpu_cb);

    std::cout << "Start simulation with PC=" << std::hex << loader->getEntryPoint()
	      << std::dec << std::endl;
    cpu->setPC(loader->getEntryPoint());
    int ninsts = 100 * 1000 * 1000;
    cpu->step(ninsts);
    std::cout << ninsts << " (" << ninsts / 1000000 << "M) Insts simulated.\n";
}

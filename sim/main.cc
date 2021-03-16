
#include <arch/riscv/cpu.h>
#include <base/elf-loader/ExeLoader.h>
#include <base/mem-image/MemImage.h>

using namespace NS_ExeLoader;
using namespace NS_MemImage;

//using ExeLoader::addr_t;
using prop_t = ExeLoader::prop_t;
//using ExeLoader::size_t;

int main()
{
    MemImage *mim = createMemImage("simple");

    // hello.elf is compiled from test/riscv/hello-asm
    ExeLoader *loader = createExeLoader("hello.elf");

    ExeLoader::CallBack ld_cb;
    ld_cb.loadData = [mim](uint64_t pa, void* data, uint32_t size, prop_t){
        mim->writeMem(pa, data, size);
    };
    ld_cb.setZero = [mim](uint64_t pa, uint32_t size, prop_t){
        mim->clear(pa, size);
    };
    loader->setCallBack(ld_cb);

    loader->loadFile();

    using riscv::CPU;
    CPU *cpu = new riscv::CPU();
    CPU::CallBack cpu_cb;

    cpu_cb.fetchInst = [mim](CPU*,uint64_t pc,uint32_t *pinst) {
        mim->readMem(pc, pinst, sizeof(*pinst));
    };
    cpu_cb.readMemory = [mim](CPU*,uint64_t pa,void *buf,int size) {
        mim->readMem(pa, buf, size);
    };
    cpu_cb.writeMemory = [mim](CPU*,uint64_t pa,void *buf,int size) {
        mim->writeMem(pa, buf, size);
    };
    cpu->setCallBack(cpu_cb);

    cpu->step(100);
}

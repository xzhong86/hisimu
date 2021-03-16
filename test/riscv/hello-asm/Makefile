
GCC     = riscv64-linux-gnu-gcc
OBJDUMP = riscv64-linux-gnu-objdump

hello.elf: hello.S
	$(GCC) -march=rv64g -nostdlib -o $@ $<

%.dump: %.elf
	$(OBJDUMP) -D $< > $@

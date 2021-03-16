
GCC     = riscv64-linux-gnu-gcc
OBJDUMP = riscv64-linux-gnu-objdump

hello.elf: hello.S
	$(GCC) -nostdlib -o $@ $<

%.dump: %.elf
	$(OBJDUMP) -D $< > $@


PREFIX  = riscv64-linux-gnu-
#PREFIX  = riscv64-unknown-elf-
GCC     = $(PREFIX)gcc
OBJDUMP = $(PREFIX)objdump

hello.elf: hello.S
	$(GCC) -march=rv64g -static -nostdlib -o $@ $<

%.dump: %.elf
	$(OBJDUMP) -D $< > $@


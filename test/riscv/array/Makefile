
#PREFIX = riscv64-unknown-elf-
PREFIX  = riscv64-linux-gnu-
GCC     = $(PREFIX)gcc
OBJDUMP = $(PREFIX)objdump

test.elf : main.c start.S
	$(GCC) -O2 -static -fno-PIC -nostdlib -march=rv64g -Wl,-Ttext=0x4000 -Wl,--build-id=none -o $@ $^

dump : test.elf
	$(OBJDUMP) -D $< > $@

#$(GCC) -O2 -static -specs=htif_nano.specs -o $@ $<


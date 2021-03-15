
RUBY = ruby -I ../../utils/isa-parser
GEN_CODE = $(RUBY) script/gen-c-code.rb isa-def/*.def

CFLAGS = -I../..

VPATH += gen/

all: init test.elf
.PHONY: all clean

test.elf : test.o decode_exec.o simple-decoder.o
	$(CC) -o $@ $^

init:
	mkdir -p gen

gen/decode_exec.c : $(ISA_FILES)
	$(GEN_CODE) -G decode_exec -o $@

gen/simple-decoder.c : simple-decoder-temp.c
	$(GEN_CODE) -T $< -o $@


%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm gen/* *.o test.elf


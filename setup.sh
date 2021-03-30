#!/bin/sh
# simple script to setup environment.

root=$PWD

[ -e base/mem-image/MemImage.h ] || git submodule update --init --recursive

cd $root/utils/isa-parser/
[ -e gen/isa-def.racc.rb ] || ./run.sh > /dev/null

cd $root/arch/riscv/
[ -e gen/decode_exec.c ] || make

#cd $root/test/riscv/hello-asm/
#[ -e hello.dump ] || make hello.dump

mkdir -p $root/build
cd $root/build
[ -e hello.elf ] || ln -s ../test/riscv/hello-asm/hello.elf hello.elf

[ -e Makefile ]  || cmake ..
[ -e hisimu ]    || make


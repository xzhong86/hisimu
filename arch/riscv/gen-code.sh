#!/bin/sh

mkdir -p gen

ruby="ruby -I ../../utils/isa-parser"
gen_code="$ruby isa-def/gen-c-code.rb"

gcc="gcc -I../.."

$gen_code -G decode_exec -o gen/decode_exec.c

$gcc -c -o decode_exec.o gen/decode_exec.c 

$gen_code -T isa-def/simple-decoder.c -o gen/simple-decoder.c
 
$gcc -c -o simple-decoder.o gen/simple-decoder.c

$gcc -c -o test.o test.c
gcc -o test.elf test.o simple-decoder.o decode_exec.o

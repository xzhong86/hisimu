#!/bin/sh

mkdir -p gen

ruby -I ../../utils/isa-parser isa-def/gen-c-code.rb -o gen/decode_exec.c



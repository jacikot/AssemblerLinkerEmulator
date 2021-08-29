#!/bin/bash

g++ -std=c++17 -Wall -o linker src/*.cpp -Iinc -Ibuild 2> errors.txt
./linker -hex -place=ivt@0x0000 -o program.hex ./tests/in.o ./tests/in2.o
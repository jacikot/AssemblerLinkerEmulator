#!/bin/bash

g++ -std=c++17 -Wall -o linker Linker/src/*.cpp -Iinc -Ibuild 2> errors.txt
linker -hex -place=ivt@0x0000 -o program.hex in.o in2.o
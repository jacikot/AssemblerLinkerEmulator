#!/bin/bash

g++ -std=c++17 -Wall -o emulator src/*.cpp -Iinc -Ibuild 2> errors.txt
./emulator ./tests/program.hex
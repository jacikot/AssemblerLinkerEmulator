#!/bin/bash

g++ -std=c++17 -Wall -o linker Linker/src/*.cpp -Iinc -Ibuild 2> errors.txt
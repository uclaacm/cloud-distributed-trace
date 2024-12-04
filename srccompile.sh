#!/bin/bash
g++ -I include src/testprog.cpp -o build/testprog.o -L build -l dtrace

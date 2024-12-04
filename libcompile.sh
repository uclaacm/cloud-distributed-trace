#!/bin/bash
g++ -I ./include/ -c lib/test.cpp -o build/test.o
ar rcs build/libdtrace.a build/test.o

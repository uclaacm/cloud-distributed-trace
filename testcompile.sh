#!/bin/bash
g++ -I include tests/test_test.cpp -o build/run_tests -L build -l dtrace -std=c++17
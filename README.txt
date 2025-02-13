DIRECTORY DESCRIPTIONS
build: final compilation output here (.so file for lib, output for src)
include: interface for library (.h)
lib: implementation for library (.cpp)
src: test application using the lib implementation
tests: unit tests for lib functions

Current State
I put some test files into the directories so you
can see what's going on. libcompile.sh compiles
the library code. srccompile.sh compiles a sample
program using the library.

How to Run
Copy and Paste the commands into terminal from
project root directory (same dir as this README).
Must be running on Linux.
---COMMAND START---
cmake -S . -B build
cd build && make && cd ..
----COMMAND END----
Explanation: 1) Compile library. 2) Compile src
program. 3) run src program (testprog.o).
Should output "Hello".

Build Pipeline Objectives
Migrate from the bash shell scripts to a more
robust build system, probably CMake or something.

Build Requirements:
Should be robust. As long as a convention is
followed, all new code should compile properly (ie
all headers in the include dir, cpp files in the
proper places, etc).

(Spec)
make - build both the library and the src program
make lib - build only the library
make src - build only the src program
make clean - remove build artifacts
./deploy.sh - start docker containers + run prog

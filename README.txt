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

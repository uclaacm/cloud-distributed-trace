#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

#define TRACE_CALL(fn, ...) \
    std::cout << "Calling " << #fn << " from " << __FILE__ << ":" << __LINE__ << std::endl; \
    fn(__VA_ARGS__);

void function1();
void function2();
void function3();

#endif

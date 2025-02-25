#include <iostream>
#include <unistd.h>

int main() {
  while (true) {
    std::cout << "Test program" << std::endl;  // Here you need to set a breakpoint
    sleep(5);
  }
  return 0;
}

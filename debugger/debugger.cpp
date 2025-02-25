#include <lldb/API/LLDB.h>
#include <iostream>

using namespace lldb;

int main() {
  SBDebugger::Initialize();
  auto debugger = SBDebugger::Create(true);
  debugger.SetAsync(false);

  auto target = debugger.CreateTarget("a.out");
  if (!target.IsValid()) {
      std::cerr << "Failed to create target.\n";
      return 1;
  }

  auto breakpoint = target.BreakpointCreateByLocation("main.cpp", 5);  // Breakpoint location in the program being debugged
  if (!breakpoint.IsValid()) {
      std::cerr << "Failed to create breakpoint.\n";
      return 1;
  }
 
  std::cout << "Printing works" << std::endl;

  auto process = target.LaunchSimple(nullptr, nullptr, nullptr);
  if (!process.IsValid()) {
      std::cerr << "Failed to launch process.\n";
      return 1;
  }

  std::cout << "Printing works" << std::endl;

  auto info = process.GetProcessInfo();
  std::cout << "ProcessID: " << info.GetProcessID() << std::endl;
  std::cout << "Name: " << info.GetName() << std::endl;

  SBDebugger::Terminate();
  return 0;
}


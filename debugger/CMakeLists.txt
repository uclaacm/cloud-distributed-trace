# STEPS TO SET UP ENVIRONMENT:
# 1. Install lldb and liblldb-dev
# 2. Check if you get "error: unable to locate lldb-server-14.0.0" when running
# 3. If you get the above error, create a symlink from lldb-server-14.0.0 to lldb-server


cmake_minimum_required(VERSION 3.15)
project(debugger)

# Set LLDB include and library paths manually
include_directories(/usr/include/lldb)
link_directories(/usr/lib/liblldb.so)

# Add executable
add_executable(my_lldb_app debugger.cpp)

# Link LLDB dynamically
target_link_libraries(my_lldb_app PRIVATE lldb)

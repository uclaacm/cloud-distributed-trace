set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.15)

project(distributed-tracing VERSION 1.0 LANGUAGES CXX)

set(BUILD_DIRECTORY build)
set(LIB_NAME dtrace)

# specify output folder for compiled code
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIRECTORY})

# build the necessary library
file(GLOB LIB_SOURCES "lib/*.cpp")

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC include)

# add library to the main executable
add_executable(testprog src/testprog.cpp)
target_link_libraries(testprog PRIVATE ${LIB_NAME})

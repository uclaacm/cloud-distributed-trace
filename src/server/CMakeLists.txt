set(EXEC_NAME server)

file(GLOB SERVER_SOURCES "*.cpp")
add_executable(${EXEC_NAME} ${SERVER_SOURCES})
target_link_libraries(${EXEC_NAME} PRIVATE ${LIB_NAME})
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

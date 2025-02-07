set(EXEC_NAME client)

add_executable(${EXEC_NAME} client.cpp)
target_link_libraries(${EXEC_NAME} PRIVATE ${LIB_NAME})
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

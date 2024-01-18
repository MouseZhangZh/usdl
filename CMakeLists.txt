cmake_minimum_required(VERSION 3.27)
project(usdl)

set(CMAKE_CXX_STANDARD 17)

include_directories(3rd)

add_subdirectory(server)
add_subdirectory(client)

add_executable(usdl main.cpp)

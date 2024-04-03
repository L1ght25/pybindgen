cmake_minimum_required(VERSION 3.20)
project(pybindgen)

set(CPPFLAGS "-I/opt/homebrew/Cellar/llvm/17.0.6_1/include/c++/v1")
set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH OFF)

add_subdirectory(extern/pybind11)
include_directories(extern/pybind11/include)

add_subdirectory(pybind_example)
add_subdirectory(src)
add_subdirectory(lib_example)
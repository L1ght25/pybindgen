cmake_minimum_required(VERSION 3.20)
project(pybindgen)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/pybind11)
include_directories(extern/pybind11/include)

add_subdirectory(pybind_example)
add_subdirectory(src)
add_subdirectory(lib_example)
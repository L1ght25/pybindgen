cmake_minimum_required(VERSION 3.20)
project(pybindgen)

add_subdirectory(extern/pybind11)
include_directories(extern/pybind11/include)

add_subdirectory(pybind_example)

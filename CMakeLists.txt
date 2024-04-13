cmake_minimum_required(VERSION 3.20)
project(pybindgen)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(LIBNAME main_lib)
endif ()

add_subdirectory(extern/pybind11)
include_directories(extern/pybind11/include)

add_subdirectory(src)
add_subdirectory(lib_example)

add_subdirectory(py_build)

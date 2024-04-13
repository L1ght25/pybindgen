# pybindgen
Program for automatic pybind11 generation

## Getting started

To generate python bindigs for your C++ library, you need to:

* Clone this repo to your project, add to build to CMake, set LIBNAME flag to name of target of the library:

```cmake
SET(LIBNAME <requested library>)
ADD_SUBDIRECTORY(pybindgen)
```

* go to your build directory, then to `pybindgen/py_build` and run:

```bash
make py_<requested library>
```

* After this, `.so` file with python library will be in this directory.

## Pay attention!

* Name of your library in python will be with prefix `py_`. For example, if you have library named `UltraLib`, in python it will be `py_UltraLib`.

* To build your library correctly you need to build in `Release` mode.

* Bindings will be done for all objects that are in `*.h` files of the directories specified in `target_include_directories` in CMake file of your library. There won't be bindings for objects in external headers. For example, if you have
```c++
#include <iostream>
```
Objects from `iostream` won't be binded.
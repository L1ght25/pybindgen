set(LIBNAME main_lib)


set(CMAKE_CXX_STANDARD 20)

# Создание пустого исходного файла, который будет перезаписан после сборки
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp "")

find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${Clang_INCLUDE_DIRS})


separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(main)

target_sources(main PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/matcher.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

add_dependencies(main ${LIBNAME})

target_link_libraries(main
    PRIVATE
    clangTooling
)


add_custom_command(TARGET main POST_BUILD
  COMMAND echo "Include directories: $<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>, >"
  COMMAND $<TARGET_FILE:main> --python-lib-name=py_${LIBNAME} --generated-file-path=${CMAKE_CURRENT_BINARY_DIR}/generated.cpp -p ${CMAKE_BINARY_DIR} "$<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>,;>"
  COMMAND_EXPAND_LISTS
  VERBATIM
  COMMENT "Generating file..."
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

pybind11_add_module(py_${LIBNAME} ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)

target_include_directories(py_${LIBNAME} PUBLIC ${${LIBNAME}_INCLUDE_DIRS})

target_link_libraries(py_${LIBNAME} PUBLIC
${LIBNAME}
)

add_dependencies(py_${LIBNAME} main)

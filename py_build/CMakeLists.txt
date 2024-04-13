# Создание пустого исходного файла, который будет перезаписан после сборки
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp "")

pybind11_add_module(py_${LIBNAME} ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)

add_custom_command(TARGET py_${LIBNAME} PRE_BUILD
  COMMAND echo "Include directories: $<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>, >"
  COMMAND $<TARGET_FILE:main> --python-lib-name=py_${LIBNAME} --generated-file-path=${CMAKE_CURRENT_BINARY_DIR}/generated.cpp -p ${CMAKE_BINARY_DIR} "$<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>,;>"
  COMMAND_EXPAND_LISTS
  VERBATIM
  COMMENT "Generating file..."
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(py_${LIBNAME} PUBLIC ${${LIBNAME}_INCLUDE_DIRS})
target_link_libraries(py_${LIBNAME} PUBLIC
${LIBNAME}
)

add_dependencies(py_${LIBNAME} main)

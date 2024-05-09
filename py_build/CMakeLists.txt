add_custom_command(
  COMMAND echo "Include directories: $<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>, >"
  COMMAND $<TARGET_FILE:main> --python-lib-name=py_${LIBNAME} --generated-file-path=${CMAKE_CURRENT_SOURCE_DIR}/generated.cpp -p ${CMAKE_BINARY_DIR} "$<JOIN:$<TARGET_PROPERTY:${LIBNAME},INTERFACE_INCLUDE_DIRECTORIES>,;>"
  COMMAND_EXPAND_LISTS
  VERBATIM
  COMMENT "Generating file..."
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/generated.cpp
)

pybind11_add_module(py_${LIBNAME} ${CMAKE_CURRENT_SOURCE_DIR}/generated.cpp)

target_include_directories(py_${LIBNAME} PUBLIC ${${LIBNAME}_INCLUDE_DIRS})
target_link_libraries(py_${LIBNAME} PUBLIC
  ${LIBNAME}
)

add_dependencies(py_${LIBNAME} main)

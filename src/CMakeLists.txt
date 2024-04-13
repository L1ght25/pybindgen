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

target_link_libraries(main
    PRIVATE
    clangTooling
)

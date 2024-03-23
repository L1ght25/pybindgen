set(LLVM_DIR "/opt/homebrew/Cellar/llvm/17.0.6_1/lib/cmake/llvm/")
set(Clang_DIR "/opt/homebrew/Cellar/llvm/17.0.6_1/lib/cmake/clang/")

set(CMAKE_CXX_STANDARD 20)


find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${Clang_INCLUDE_DIRS})


separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(main)

target_sources(main PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# llvm_map_components_to_libnames(llvm_libs Core Support IRReader)
# target_link_libraries(main ${llvm_libs})

target_link_libraries(main
    PRIVATE
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangTooling
    clangToolingCore
    )

# target_compile_options(main PRIVATE "-fno-rtti")

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
  ${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

add_dependencies(main main_lib)

target_link_libraries(main
    PRIVATE
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangTooling
    clangToolingCore
    )

add_custom_command(TARGET main POST_BUILD
    COMMAND cp
            $<TARGET_FILE:main_lib>
            ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND echo \"$<TARGET_FILE:main_lib>\" > ${CMAKE_CURRENT_BINARY_DIR}/lib_file
    COMMENT "Copying library to build directory"
)
set(CMAKE_CXX_STANDARD 20)

add_library(main_lib main.cpp)

target_sources(main_lib PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(main_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
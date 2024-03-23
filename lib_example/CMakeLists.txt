set(CMAKE_CXX_STANDARD 20)

add_executable(main_lib)

target_sources(main_lib PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


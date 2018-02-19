cmake_minimum_required(VERSION 2.8)
project(cpsl)

set(EXTRA_COMPILE_FLAGS "-g3 -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(cpsl_srcs
  source/main.cpp
  ../source/expressions.cpp
  ../source/symbol_table.cpp
  ../source/register_pool.cpp
)
source_group("CPSL_TESTS" FILES ${cpsl_srcs})

add_executable(cpsl_tests ${cpsl_srcs})
target_link_libraries(cpsl_tests )


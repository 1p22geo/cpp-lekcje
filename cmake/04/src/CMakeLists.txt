cmake_minimum_required(VERSION 3.10.0)

project(euler)

add_library(asserts SHARED asserts.c)
add_library(bignums SHARED bignums.c)
target_link_libraries(bignums m) # libmath.so

add_executable(test_bignums test_bignums.c)

target_link_libraries(test_bignums asserts)
target_link_libraries(test_bignums bignums)

add_executable(test_arithmetic test_arithmetic.c)

target_link_libraries(test_arithmetic asserts)
target_link_libraries(test_arithmetic bignums)

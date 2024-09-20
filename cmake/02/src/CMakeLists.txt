include(src/lib_list/CMakeLists.txt)

add_executable(main src/main.cpp src/main.hpp)
target_include_directories(main PUBLIC src/)
target_link_libraries(main PUBLIC lib_list)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(main src/main.cpp src/function1.cpp)
target_include_directories(main PUBLIC src/lib1 src/lib2)
target_link_libraries(main PUBLIC lib1 lib2)

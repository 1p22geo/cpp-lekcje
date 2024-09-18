set_source_files_properties(src/lib2/main.s PROPERTIES LANGUAGE ASM_NASM)
add_library(lib2 STATIC src/lib2/main.cpp src/lib2/main.s)

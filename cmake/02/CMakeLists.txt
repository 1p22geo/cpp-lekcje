cmake_minimum_required(VERSION 3.30)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
project(DoubleLinkedList LANGUAGES CXX C ASM_NASM)

include(src/CMakeLists.txt)

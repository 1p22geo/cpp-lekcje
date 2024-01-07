cmake_minimum_required(VERSION 3.24)
project(Figury)
add_library("trojkat" "trojkat.cpp")
add_library("prostokat" "prostokat.cpp")
add_library("figura" "figura.cpp")
add_executable("figury" "main.cpp")
target_link_libraries(figury 
                      PUBLIC trojkat 
                      PUBLIC prostokat 
                      PUBLIC figura
                      )

install(TARGETS figury DESTINATION /bin)

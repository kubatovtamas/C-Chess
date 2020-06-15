cmake_minimum_required(VERSION 3.0)
project(Sakk C)

add_subdirectory(Lib)


add_executable(main main.c)
target_link_libraries(main libsakk)

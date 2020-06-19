cmake_minimum_required(VERSION 3.0)
project(Sakk C)

include_directories(src
                    "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tst)
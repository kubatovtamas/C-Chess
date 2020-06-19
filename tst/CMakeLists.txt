enable_testing()
add_executable(utest-piece utest-piece.c)

set_target_properties (utest-piece PROPERTIES LINK_FLAGS -Wl,-lcunit)

add_test (utest-piece ${EXECUTABLE_OUTPUT_PATH}/utest-piece)
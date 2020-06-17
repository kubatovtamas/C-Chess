add_executable(utest-main utest-main.c)
add_executable(utest-lib utest-lib.c utest-board.c utest-piece.c utest-filehandler.c)
target_link_libraries(utest-main libsakk)
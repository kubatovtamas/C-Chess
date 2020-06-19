//
// Created by gigi on 6/17/20.
//

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "utest-filehandler.h"
#include "board.h"

void test_load_from_file() {
    /*bool load_from_file(char *input_name, int *global_round_count,
                    char *global_p1_name, char *global_p2_name,
                    PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE])*/
}
void test_save_to_file() {

}


CU_TestInfo filehandler_tests[] = {
    {"load_test",               test_load_from_file},
    {"save_test",               test_save_to_file},
    CU_TEST_INFO_NULL
};

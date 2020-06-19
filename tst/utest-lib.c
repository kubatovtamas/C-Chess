//
// Created by gigi on 6/17/20.
//


// Lib tests
//#include "lib/libsakk.h"
#include "utest-filehandler.h"
#include "utest-game.h"

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo libsakk_suites[] = {
    {"game_state", NULL, NULL, utest_game_setup, utest_game_teardown, game_state_tests },
    /* { "libsakk", NULL, NULL, TEST_SETUP, TEST_TEARDOWN, libsakk_tests },
    { "piece", NULL, NULL, NULL, NULL, piece_tests },
    { "board", NULL, NULL, NULL, NULL, board_tests }, */
    { "filehandler", NULL, NULL, NULL, NULL, filehandler_tests },
    CU_SUITE_INFO_NULL      // this is needed at the end
};

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return -1;
    };
    if (CU_register_suites(libsakk_suites) != CUE_SUCCESS) {
        return -1;
    };
    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

//
// Created by gigi on 6/19/20.
//

#include "utest-game.h"

void test_game_start() {
    Game* game = game_start();
    CU_ASSERT_PTR_NOT_NULL(game);
    CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, game->currentstate);
}

CU_TestInfo game_state_tests[] = {
        {"game_start",               test_game_start},
        CU_TEST_INFO_NULL
};

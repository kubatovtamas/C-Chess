//
// Created by gigi on 6/19/20.
//

#include "utest-game.h"

Game* game = NULL;

void test_game_start() {
    CU_ASSERT_PTR_NOT_NULL(game);
    CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, game->currentstate);
}

void test_new_game_state() {

}


void utest_game_setup() {
    game = game_start();
}

void utest_game_teardown() {
    game_end(game);
}


CU_TestInfo game_state_tests[] = {
        {"game_start",               test_game_start},
        {"new_game_state",           test_new_game_state},
        CU_TEST_INFO_NULL
};

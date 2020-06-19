//
// Created by gigi on 6/19/20.
// Unit tests by Gigi
//

#include "utest-game.h"

Game* game = NULL;
// displayed_game_state_ptr starts NULL in game.c

void test_game_start() {
    CU_ASSERT_PTR_NOT_NULL(game);
    CU_ASSERT_PTR_NOT_NULL(game->currentstate);
    CU_ASSERT_PTR_EQUAL(game->currentstate, displayed_game_state_ptr);
    CU_ASSERT_PTR_EQUAL(game->currentstate, displayed_game_state_ptr);
}

//void test_game_end() {
//    // there's no test for freed memory
//    // set all freed pointers to NULL check for NULL
//}

void test_undo_to_previous_state() {
    Game_State* tmp = displayed_game_state_ptr;
    undo_to_previous_state();
    if (tmp->previous) {
        CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, tmp->previous);
    } else {
        CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, tmp);
    }

}


void utest_game_setup() {
    game = game_start();
}

void utest_game_teardown() {
    game_end(game);
}


CU_TestInfo game_state_tests[] = {
        {"game_start",               test_game_start},
        //{"game_end",                 test_game_end},
        {"undo_to_previous_state",               test_undo_to_previous_state},
        CU_TEST_INFO_NULL
};

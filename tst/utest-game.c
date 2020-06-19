//
// Created by gigi on 6/19/20.
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

void test_game_end() {
    // ... there's not test for freed memory
    // possibly set all freed pointers to NULL check for NULL
    game_end(game);
    CU_ASSERT_PTR_NULL(game);
    game = game_start();
}

void test_undo_to_previous_state() {
    Game_State* tmp = displayed_game_state_ptr;
    undo_to_previous_state();
    if (tmp->previous) {
        CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, tmp->previous);
    } else {
        CU_ASSERT_PTR_EQUAL(displayed_game_state_ptr, tmp);
    }

    // Actually make moves and test that way here

}

// move_after_undo calls undo_to_previous_state and sets remaining next_ptr to NULL
void test_move_after_undo() {


};

//void test_new_position_data {
//
//};


//void test_new_game_state() {
//    Position_Data* from_position = new_position_data();
//    Position_Data* to_position = new_position_data();
//    Game_State_Data *game_state_data = new_game_state_data();
//}


void utest_game_setup() {
    game = game_start();
}

void utest_game_teardown() {
    game_end(game);
}


CU_TestInfo game_state_tests[] = {
        {"game_start",               test_game_start},
        {"game_end",                 test_game_end},
        {"undo_to_previous_state",               test_undo_to_previous_state},
        {"move_after_undo",               test_move_after_undo},
        //{"new_game_state",           test_new_game_state},
        CU_TEST_INFO_NULL
};

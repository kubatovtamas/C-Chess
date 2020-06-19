//
// Created by gigi on 6/19/20.
// Unit test by Gigi
//

#ifndef SAKK_UTEST_GAME_H
#define SAKK_UTEST_GAME_H

#include <CUnit/CUnit.h>
#include "game.h"

void utest_game_setup();
void utest_game_teardown();
void test_game_start();
void test_new_game_state();
void test_game_end();                               // game_end calls free_game_state_to_end on first state and frees game
void test_undo_to_previous_state();                 // sets displayed_game_state_ptr to previous
void test_move_after_undo();                        // calls undo_to_previous_state and sets remaining next_ptr to NULL

extern CU_TestInfo game_state_tests[];

#endif //SAKK_UTEST_GAME_H

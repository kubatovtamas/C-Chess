//
// Created by gigi on 6/19/20.
//

#ifndef SAKK_UTEST_GAME_H
#define SAKK_UTEST_GAME_H

#include <CUnit/CUnit.h>
#include "game.h"

void utest_game_setup();
void utest_game_teardown();
void test_game_start();
void test_new_game_state();


extern CU_TestInfo game_state_tests[];

#endif //SAKK_UTEST_GAME_H

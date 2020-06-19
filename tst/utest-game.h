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
void test_game_end();                               // game_end calls free_game_state_to_end on first state and frees game
void test_undo_to_previous_state();                 // sets displayed_game_state_ptr to previous
void test_move_after_undo();                        // calls undo_to_previous_state and sets remaining next_ptr to NULL

//void new_game_state(Game*, Game_State_Data*);    // creates new game state and links it to game->last
//void free_game_state(Game_State*);               // free Game_State data and free Game_State
//void free_game_state_data(Game_State_Data* game_state_data);    // free game_state_data and game_state_data positions
//void free_game_state_to_end(Game_State*);        // iterate through Game_States from node and free all of them
//
//
//// creates a new Game_State_Data according to parameters
//Game_State_Data* new_game_state_data(Position_Data*, Position_Data*, Position_Data*, Position_Data*);

extern CU_TestInfo game_state_tests[];

#endif //SAKK_UTEST_GAME_H

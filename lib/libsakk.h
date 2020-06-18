//
// Created by gigi on 6/12/20.
//

#ifndef C_CHESS_LIBSAKK_H
#define C_CHESS_LIBSAKK_H

#include <stdbool.h>
// include all library headers
#include "piece.h"
#include "board.h"
#include "filehandler.h"

// Possibly move these somewhere more sensible
extern int round_count;         // round count global
// bool is_even(int n);            // tool to check round count for next color

typedef struct Game Game;                                      // Game structure linking game states
typedef struct Game_State Game_State;                          // Game_State nodes for a single game state
typedef struct Game_State_Data Game_State_Data;                // Game_State_Data data for Game_State nodes


Game* game_start();                             // sets Game_State first and last to default Game_State (Game_Data is null)
void game_end(Game*);                           // calls free_game_state_to_end on first state and frees game
void new_game_state(Game*);                      // creates new game state and links it to game->last
// TODO rename new_game_state for use in main

void free_game_state(Game_State*);               // free Game_State data and free Game_State
void free_game_state_to_end(Game_State*);        // iterate through Game_States from node and free all of them


#endif // C_CHESS_LIBSAKK_H

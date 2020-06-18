//
// Created by gigi on 6/18/20.
//

#ifndef SAKK_GAME_H
#define SAKK_GAME_H

#include "piece.h"

typedef struct Game Game;                                      // Game structure linking game states
typedef struct Game_State Game_State;                          // Game_State nodes for a single game state
typedef struct Game_State_Data Game_State_Data;                // Game_State_Data data for Game_State nodes


Game* game_start();                             // sets Game_State first and last to default Game_State (Game_Data is null)
void game_end(Game*);                           // calls free_game_state_to_end on first state and frees game

void new_game_state(Game*, Game_State_Data*);    // creates new game state and links it to game->last
void free_game_state(Game_State*);               // free Game_State data and free Game_State
void free_game_state_to_end(Game_State*);        // iterate through Game_States from node and free all of them

// creates a new Game_State_Data according to parameters
Game_State_Data* new_game_state_data(char**, PIECE_T*, PIECE_T*);


#endif //SAKK_GAME_H

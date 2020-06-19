//
// Created by gigi on 6/18/20.
//

#ifndef SAKK_GAME_H
#define SAKK_GAME_H

#include "piece.h"

/************* Game ******************/
typedef struct Game {
    struct Game_State *defaultstate;                 // this link will always point to first Link (default board)
    struct Game_State *currentstate;                 // this link will always point to last Link
} Game;

/************* Game State ****************/

// Game_State structure implemented as a Doubly-linked list (idea by Kuba)
// A Round holds a pointer to the next round (init NULL) and the previous Round.
// The Step struct holds the data for the moves of the current round.
// Outline implementation and modification by Gigi

typedef struct Game_State {
    struct Game_State_Data* data;
    struct Game_State* previous;
    struct Game_State* next;
} Game_State;


/************** Game_State_Data ***************/
// Step struct idea and pseudocode by Kuba
// Modified by Gigi
typedef struct Game_State_Data {
    char tiles[4][2];                      // e.g. normal move: [C2, C3, NULL, NULL]
    PIECE_T before[2];                   // moved piece before move
    PIECE_T after[2];                    // after move (info new position and if promoted)
    //PIECE_T hit;                       // piece that was hit and moved out of play
} Game_State_Data;


extern Game_State *displayed_game_state_ptr;

Game* game_start();                             // sets Game_State first and last to default Game_State (Game_Data is null)
void game_end(Game*);                           // calls free_game_state_to_end on first state and frees game

void undo_to_previous_state(Game *game);
void new_game_state(Game*, Game_State_Data*);    // creates new game state and links it to game->last
void free_game_state(Game_State*);               // free Game_State data and free Game_State
void free_game_state_to_end(Game_State*);        // iterate through Game_States from node and free all of them

// creates a new Game_State_Data according to parameters
Game_State_Data* new_game_state_data(char*[4], PIECE_T*, PIECE_T*);


#endif //SAKK_GAME_H
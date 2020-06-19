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
//    int fromTile[2];                     // col then row (letter, number)
//    int toTile[2];                       // letter, number
    char tiles[4][2];
    PIECE_T before[2];                   // moved piece before move
    PIECE_T after[2];                    // after move (info new position and if promoted)
} Game_State_Data;

//typedef struct Game_State_Data {
//    struct Position_Data *fromPosition;             // from position and piece_type at location
//    struct Position_Data *toPosition;               // to position and piece_type at location
//} Game_State_Data;
//


extern Game_State *displayed_game_state_ptr;

Game* game_start();                             // sets Game_State first and last to default Game_State (Game_Data is null)
void game_end(Game*);                           // calls free_game_state_to_end on first state and frees game


void move_after_undo(Game*, Game_State*);         // calls undo_to_previous_state and sets remaining next_ptr to NULL
void undo_to_previous_state();                   // sets displayed_game_state_ptr to previous
void new_game_state(Game*, Game_State_Data*);    // creates new game state and links it to game->last
void free_game_state(Game_State*);               // free Game_State data and free Game_State
void free_game_state_data(Game_State_Data* game_state_data);    // free game_state_data and game_state_data positions
void free_game_state_to_end(Game_State*);        // iterate through Game_States from node and free all of them


// creates a new Game_State_Data according to parameters
Game_State_Data* new_game_state_data(char[4][2], PIECE_T*, PIECE_T*);
//Game_State_Data* new_game_state_data(int from[2], int to[2], PIECE_T*, PIECE_T*);
//Game_State_Data* new_game_state_data(Position_Data*);
//Position_Data* new_position_data(PIECE_T type, int row, int col);

void debug_print_game(Game* game);

#endif //SAKK_GAME_H

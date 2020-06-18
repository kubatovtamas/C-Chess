//
// Created by gigi on 6/18/20.
//

#include <stdlib.h>     // NULL
#include <string.h>     // memcpy

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
    char* tiles[4];                      // e.g. normal move: [C2, C3, NULL, NULL]
    PIECE_T before[2];                   // moved piece before move
    PIECE_T after[2];                    // after move (info new position and if promoted)
    //PIECE_T hit;                         // piece that was hit and moved out of play
} Game_State_Data;

// sets Game_State first and last to default Game_State (Game_Data is null)
Game* game_start() {
    struct Game *game = malloc(sizeof(Game));
    if (!game) { return NULL; }  // failed to allocate

    // Default state
    Game_State *defaultstate = malloc(sizeof(Game_State));
    defaultstate->previous= NULL;
    defaultstate->data = NULL;
    defaultstate->next = NULL;

    game->defaultstate = defaultstate;
    game->currentstate = game->defaultstate;

    return game;
}

// insert a link to the new state to the end of the list
// - Gigi
void new_game_state(Game* game, Game_State_Data *game_state_data) {
    Game_State *newstate = malloc(sizeof(Game_State));       //create a link

    newstate->data = game_state_data;

    (game->currentstate)->next = newstate;
    newstate->previous = game->currentstate;
    game->currentstate = newstate;
}

// free Game_State data and free Game_State
void free_game_state(Game_State* game_state) {
    if (game_state->data) {
        free(game_state->data);
    }
    free(game_state);
}

// iterate through Game_States from node and free all of them
void free_game_state_to_end(Game_State* game_state) {
    Game_State *next = game_state;                  // starting node to delete from

    while(next) {
        Game_State *game_state = next;              // set current Game_State to next in list
        next = game_state->next;
        free_game_state(game_state);                // free current Game_State
    }

}

// free_game_state_to_end(game->first) and free(game);
void game_end(Game* game) {
    free_game_state_to_end(game->defaultstate);

    free(game);
}

// intializes new game_state_data for game data based on parameters
Game_State_Data* new_game_state_data(char* tiles[4], PIECE_T before[2], PIECE_T after[2]) {
    Game_State_Data *game_state_data = malloc(sizeof(Game_State_Data));

    memcpy(game_state_data->tiles, tiles, 4*sizeof(char*));
    memcpy(game_state_data->before, before, 2*sizeof(PIECE_T));
    memcpy(game_state_data->after, after, 2*sizeof(PIECE_T));
    //game_state_data->hit = hit;

    return game_state_data;
}
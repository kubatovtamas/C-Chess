//
// Created by gigi on 6/18/20.
//

#include <stdlib.h>     // NULL
#include <string.h>     // memcpy

#include "piece.h"
#include "game.h"
#include "libsakk.h"


Game_State* displayed_game_state_ptr = NULL;

// sets Game_State first and last to default Game_State (Game_Data is null)
Game* game_start() {
    Game *game = malloc(sizeof(Game));
    if (!game) { return NULL; }  // failed to allocate

    // Default state
    Game_State *defaultstate = malloc(sizeof(Game_State));
    defaultstate->previous= NULL;
    defaultstate->data = NULL;
    defaultstate->next = NULL;

    game->defaultstate = defaultstate;
    game->currentstate = game->defaultstate;
    displayed_game_state_ptr = game->currentstate;

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
    displayed_game_state_ptr = game->currentstate;
    newstate->next = NULL;
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

    for(int i = 0; i < 4; i++ ) {
        if (tiles[i]) {
            memcpy(game_state_data->tiles[i], tiles[i], sizeof(game_state_data->tiles[i]));
        } else {
            tiles[i] = NULL;
        }
    }

    memcpy(game_state_data->before, before, sizeof(game_state_data->before));
    memcpy(game_state_data->after, after, sizeof(game_state_data->after));
    //game_state_data->hit = hit;

    return game_state_data;
}


void undo_to_previous_state(Game *game) {
    if (displayed_game_state_ptr->previous == NULL) {
        return;
    }
    displayed_game_state_ptr = displayed_game_state_ptr->previous;
}
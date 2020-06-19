//
// Created by gigi on 6/18/20.
//

#include <stdlib.h>     // NULL
#include <string.h>     // memcpy
#include <wchar.h>      // debug print

#include "piece.h"
#include "game.h"
#include "libsakk.h"
#include "position.h"

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
    // create link
    Game_State *newstate = malloc(sizeof(Game_State));
    // setup
    newstate->next = NULL;
    newstate->previous = game->currentstate;
    newstate->data = game_state_data;

    // append to end of linked list
    (game->currentstate)->next = newstate;
    // set list end pointer to new node
    game->currentstate = newstate;

    // set currently displayed state
    displayed_game_state_ptr = game->currentstate;

}

// free Game_State data and free Game_State
void free_game_state(Game_State* game_state) {
    if (game_state->data) {
        free_game_state_data(game_state->data);
    }
    Game_State *tmp = game_state;
    game_state = NULL;
    free(tmp);
}


void free_game_state_data(Game_State_Data* game_state_data) {
    if (game_state_data->fromPosition) {
        Position_Data *tmp = game_state_data->fromPosition;
        game_state_data->fromPosition = NULL;
        free(tmp);
    }
    if (game_state_data->toPosition) {
        Position_Data *tmp = game_state_data->toPosition;
        game_state_data->toPosition = NULL;
        free(tmp);
    }
    if (game_state_data->fromCastle) {
        Position_Data *tmp = game_state_data->fromCastle;
        game_state_data->fromCastle = NULL;
        free(tmp);
    }
    if (game_state_data->toCastle) {
        Position_Data *tmp = game_state_data->toCastle;
        game_state_data->toCastle = NULL;
        free(tmp);
    }

    Game_State_Data *tmp = game_state_data;
    game_state_data = NULL;
    free(tmp);
}

// iterate through Game_States from node and free all of them
void free_game_state_to_end(Game_State* game_state) {
    Game_State* tmp;

    while(game_state) {
        tmp = game_state;
        game_state = game_state->next;
        free_game_state(tmp);
    }

}

// free_game_state_to_end(game->first) and free(game);
void game_end(Game* game) {
    free_game_state_to_end(game->defaultstate);

    Game *tmp = game;
    game = NULL;
    free(tmp);
}

Game_State_Data* new_game_state_data(Position_Data* fromPosition, Position_Data* toPosition, Position_Data* fromCastle, Position_Data* toCastle) {
    Game_State_Data *game_state_data = malloc(sizeof(Game_State_Data));

    game_state_data->fromPosition = fromPosition;
    game_state_data->toPosition = toPosition;
    game_state_data->fromCastle = fromCastle;
    game_state_data->toCastle = toCastle;

    return game_state_data;
}


void undo_to_previous_state() {
    if (!displayed_game_state_ptr->previous) {
        return;
    }
    displayed_game_state_ptr = displayed_game_state_ptr->previous;
}

void move_after_undo(Game* game, Game_State* game_state) {
    if (!displayed_game_state_ptr->next) { return; }

    free_game_state_to_end(game_state->next);

    displayed_game_state_ptr = game_state;
    game->currentstate = game_state;
}

void debug_print_game(Game* game) {
    #ifdef DEBUG
    Game_State *next_state = game->defaultstate;

    wprintf(L"Current: %x\n", displayed_game_state_ptr);

    for(int i = 0; next_state; i++) {
        wprintf(L"%d: %x\n", i, next_state);
        wprintf(L"\tprevious: %x\n", next_state->previous);
        wprintf(L"\tnext: %x\n", next_state->next);
        next_state = next_state->next;
    }

    wprintf(L"Last: %x\n", game->currentstate);
    #endif
}
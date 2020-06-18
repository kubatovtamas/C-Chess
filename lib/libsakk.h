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

// Step struct idea and pseudocode by Kuba
// Modified by Gigi
struct Step {
    //tiles: [C2, C3];            // Array of Tiles, min:2(normal), max: 4(castling)
    //before: [WHITEPAWN, NULL];  // Array of Pieces
    //after: [NULL, WHITEPAWN];   // Array of Pieces
    // TODO add parameters for castling

    PIECE_T before[2];                   // moved piece before move
    PIECE_T after[2];                    // after move (info new position and if promoted)
//    PIECE_T hit;                         // piece that was hit and moved out of play
};
typedef struct Step Step;

// State structure implemented as a Doubly-linked list (idea by Kuba)
// A Round holds a pointer to the next round (init NULL) and the previous Round.
// The Step struct holds the data for the moves of the current round.
// Outline implementation and modification by Gigi
//struct State {
//    // save state changes here (before,after)
////    int key;                  // 0 default state, each change_state increments by one
//
//    Step* change_state;
//    struct State* previous;
//    struct State* next;
//};
//typedef struct State State;
//extern const struct State *defaultstate;                 // this link always point to first Link
//extern struct State *laststate;                          // this link always point to last Link

void change_state();

// This is just an outline for planned features
// TODO Proper definitions
struct State initialize();
bool save_state();
bool undo();
bool redo();

// file handling. Can be sourced to filehander.h and filehandler.c
bool save();
bool load();

#endif // C_CHESS_LIBSAKK_H

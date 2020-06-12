//
// Created by gigi on 6/12/20.
//

#ifndef C_CHESS_LIBSAKK_H
#define C_CHESS_LIBSAKK_H

#include<wchar.h>

// Pieces - Gigi
enum Piece {
 WHITEQUEEN = 0x2654,
 WHITEKING = 0x2655,
 WHITEROOK = 0x2656,
 WHITEBISHOP = 0x2657,
 WHITEKNIGHT = 0x2658,
 WHITEPAWN = 0x2659,

 BLACKQUEEN = 0x265A,
 BLACKKING = 0x265B,
 BLACKROOK = 0x265C,
 BLACKBISHOP = 0x265D,
 BLACKKNIGHT = 0x265E,
 BLACKPAWN = 0x265F
};

// State structure implemented as a Doubly-linked list (idea by Kuba)
// A Round holds a pointer to the next round (init NULL) and the previous Round.
// The Step struct holds the data for the moves of the current round.
// Outline implementation by Gigi
struct State {
    // save state changes here (before,after)
    int key;                  // 0 default state, each step increments by one

    struct Step* step;
    struct State* previous;
    struct State* next;
};

// Step struct idea and pseudocode by Kuba
struct Step {
    //tiles: [C2, C3];            // Array of Tiles, min:2(normal), max: 4(castling)
    //before: [WHITEPAWN, NULL];  // Array of Pieces
    //after: [NULL, WHITEPAWN];   // Array of Pieces
    // TODO tile implementation
    //  tiles[4];
    wchar_t before[2];
    wchar_t after[2];
};

extern const struct State *defaultstate;                 // this link always point to first Link
extern struct State *laststate;                          // this link always point to last Link

void step();                                             // change state

// This is just an outline for planned features
// TODO Proper definitions
struct State initialize();
_Bool save_state();
_Bool undo();
_Bool redo();

// file handling. Can be sourced to filehander.h and filehandler.c
_Bool save();
_Bool load();

#endif //C_CHESS_LIBSAKK_H

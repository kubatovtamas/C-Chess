//
// Created by gigi on 6/12/20.
//

#ifndef C_CHESS_LIBSAKK_H
#define C_CHESS_LIBSAKK_H



// Pieces - Gigi
enum Piece{
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


// State structure implemented as a
// Doubly-linked list (idea by Kuba)
// Outline implementation by Gigi
struct State {
    // save state changes here (before,after)
    int key;                                            // 0 default state, each step increments by one

    struct State* previous;
    struct State* next;
};

// TODO Head needs to always point to state 0 with the default board
extern struct State *defaultstate;                       // this link always point to first Link
extern struct State *laststate;                          // this link always point to last Link

void step();                                 // change state

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

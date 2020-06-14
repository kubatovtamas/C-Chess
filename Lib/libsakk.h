//
// Created by gigi on 6/12/20.
//

#ifndef C_CHESS_LIBSAKK_H
#define C_CHESS_LIBSAKK_H

#include<wchar.h>

// Pieces - Gigi
enum PIECE_TYPE {
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
typedef enum PIECE_TYPE PIECE_TYPE;

// color constants by Gigi
// white 1, black 0 (e.g. if white, go first)
enum COLOR {WHITE, BLACK};
typedef enum COLOR COLOR;

// State structure implemented as a Doubly-linked list (idea by Kuba)
// A Round holds a pointer to the next round (init NULL) and the previous Round.
// The Step struct holds the data for the moves of the current round.
// Outline implementation and modification by Gigi
struct State {
    // save state changes here (before,after)
    int key;                  // 0 default state, each step increments by one

    Step* step;
    State* previous;
    State* next;
};
typedef struct State State;
extern const struct State *defaultstate;                 // this link always point to first Link
extern struct State *laststate;                          // this link always point to last Link

// Step struct idea and pseudocode by Kuba
// Modified by Gigi
struct Step {
    //tiles: [C2, C3];            // Array of Tiles, min:2(normal), max: 4(castling)
    //before: [WHITEPAWN, NULL];  // Array of Pieces
    //after: [NULL, WHITEPAWN];   // Array of Pieces
    // TODO add parameters for castling

    Piece before;                   // moved piece before move
    Piece after;                    // after move (info new position and if promoted)
    Piece hit;                      // piece that was hit and moved out of play
};
typedef struct Step Step;

void step();                                             // change state

// bool pieceHasMoved idea by Kuba
// struct Piece and struct Position alternative idea by Gigi
struct Piece {
    PIECE_TYPE type;               // stores what type of piece
    COLOR color;                   // piece Color
    _Bool hasmoved;                     // has the piece moved so far in the game
    Position pos;                // x and y coordinates of piece location
};
typedef struct Piece Piece;

struct Position{
    int x;
    int y;
};
typedef struct Position Position;

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

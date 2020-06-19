#ifndef PIECE_H
#define PIECE_H

#include<stdbool.h>

#include "position.h"

// Pieces - Gigi
typedef enum PIECE_TYPE {
    WHITEQUEEN = 0x2655,
    WHITEKING = 0x2654,
    WHITEROOK = 0x2656,
    WHITEBISHOP = 0x2657,
    WHITEKNIGHT = 0x2658,
    WHITEPAWN = 0x2659,

    BLACKQUEEN = 0x265B,
    BLACKKING = 0x265A,
    BLACKROOK = 0x265C,
    BLACKBISHOP = 0x265D,
    BLACKKNIGHT = 0x265E,
    BLACKPAWN = 0x265F
} PIECE_T;

// color constants by Gigi
typedef enum COLOR {WHITE, BLACK} COLOR;

extern bool has_moved_white_king;              // D1
extern bool has_moved_white_rook_queenside;    // A1
extern bool has_moved_white_rook_kingside;     // H1

extern bool has_moved_black_king;              // D8
extern bool has_moved_black_rook_queenside;    // A8
extern bool has_moved_black_rook_kingside;     // H8

COLOR get_current_turn_color();
bool check_if_own_piece(int row, int col);

void change_hasmoved_values(Position_Data* from_position);


#endif // C_CHESS_PIECE_H
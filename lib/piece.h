// Piece_H by Gigi

#ifndef PIECE_H
#define PIECE_H

#include<stdbool.h>

// Pieces - Gigi
enum PIECE_TYPE {
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
};
typedef enum PIECE_TYPE PIECE_T;

// color constants by Gigi
typedef enum COLOR {WHITE, BLACK} COLOR;

COLOR get_current_turn_color();
bool check_if_own_piece(int row, int col);

#endif // C_CHESS_PIECE_H
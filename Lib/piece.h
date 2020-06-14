#ifndef PIECE_H
#define PIECE_H

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

struct Position{
    int x;
    int y;
};
typedef struct Position Position;

// bool pieceHasMoved idea by Kuba
// struct Piece and struct Position alternative idea by Gigi
struct Piece {
    PIECE_TYPE type;                // stores what type of piece
    COLOR color;                    // piece Color
    _Bool hasmoved;                 // has the piece moved so far in the game
    Position pos;                   // x and y coordinates of piece location
};
typedef struct Piece Piece;

#endif // C_CHESS_PIECE_H
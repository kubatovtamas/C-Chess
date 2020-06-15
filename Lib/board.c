//
// Created by gigi on 6/14/20.
//

#include<stdio.h>
#include<wchar.h>
#include<locale.h>
#include "board.h"
#include "piece.h"

typedef struct Position {
    Piece* piece;
    _Bool is_threatened;
} Position;

Position Board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

Position initPos() {
    Position pos;
    pos.piece = NULL;
    pos.is_threatened = 0;
    return pos;
};

void initBoard() {
    for (int iRow = 0; iRow < BOARD_ROW_SIZE; ++iRow) {
        for (int jCol = 0; jCol < BOARD_COL_SIZE; ++jCol) {
            Position pos = initPos();
            Board[iRow][jCol] = pos;
        }
    }

    // starting pieces
    // Pawns
    for (int i = 0; i < BOARD_COL_SIZE; ++i) {
        Board[1][i].piece = initPiece();
        Board[7][i].piece = initPiece();
    }

    // Rooks
    Board[0][0];
    Board[0][7];
    Board[7][0];
    Board[7][7];

    // Kings
    // Depends on which side
    // Black on top for now
    Board[0][4];
    Board[7][4];

    //Queens
    Board[0][3];
    Board[7][3];
}

void printBoard(Position **Board) {
    for (int iRow = 0; iRow < BOARD_ROW_SIZE; ++iRow) {
        for (int jCol = 0; jCol < BOARD_COL_SIZE; ++jCol) {
            Position *pos = &(Board[iRow][jCol]);
            Piece* piece = pos->piece;
            wprintf(L"%lc", piece->type);
        }
    }
}


    /*
// Board tester
PIECE_TYPE Board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
    // Black on top for now
    // top row
        {BLACKROOK, BLACKKNIGHT, BLACKBISHOP, BLACKQUEEN, BLACKKING, BLACKBISHOP, BLACKKNIGHT, BLACKROOK},
        {BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN},
        {WHITEROOK, WHITEKNIGHT, WHITEBISHOP, WHITEQUEEN, WHITEKING, WHITEBISHOP, WHITEKNIGHT, WHITEROOK}
};


void drawBoard() {
    for (int iRow = 0; iRow < BOARD_ROW_SIZE; ++iRow) {
        setlocale(LC_CTYPE, "");
        for (int jCol = 0; jCol < BOARD_COL_SIZE; ++jCol) {
            wchar_t ch = Board[iRow][jCol];
            wprintf(L" %lc ", ch);
        }
        wprintf(L"\n");
    }
}
 */
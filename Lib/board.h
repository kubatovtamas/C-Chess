//
// Created by gigi on 6/14/20.
//

#ifndef C_CHESS_BOARD_H
#define C_CHESS_BOARD_H

#include "piece.h"

enum { BOARD_ROW_SIZE = 10, BOARD_COL_SIZE = 10 };

void drawBoard();
extern PIECE_TYPE Board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

#endif //C_CHESS_BOARD_H

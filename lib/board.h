//
// Created by gigi on 6/14/20.
//

#ifndef C_CHESS_BOARD_H
#define C_CHESS_BOARD_H

#include "piece.h"

enum { BOARD_ROW_SIZE = 10, BOARD_COL_SIZE = 10 };

extern PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

void draw_board();

void reset_board();

int convert_tile_letter_to_int(char ch);

int convert_tile_number_to_int(char ch);

bool move(char *from, char *to);


#endif //C_CHESS_BOARD_H

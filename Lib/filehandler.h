//
// Created by gigi on 6/17/20.
//

#ifndef SAKK_FILEHANDLER_H
#define SAKK_FILEHANDLER_H

#include "piece.h"
#include "board.h"

void load_from_file(char* file_name, int* step, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]);
void save_to_file(char* file_name, int step, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]);

#endif //SAKK_FILEHANDLER_H

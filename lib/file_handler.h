#ifndef SAKK_FILEHANDLER_H
#define SAKK_FILEHANDLER_H

#include "piece.h"
#include "board.h"

bool load_from_file(char *input_name, int *global_round_count,
                     char *global_p1_name, char *global_p2_name, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]);
void save_to_file(char* file_name, int global_round_count, char* global_p1_name, char* global_p2_name);

#endif //SAKK_FILEHANDLER_H

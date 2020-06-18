//
// Created by gigi on 6/14/20.
//

#ifndef C_CHESS_BOARD_H
#define C_CHESS_BOARD_H

#include "game.h"
#include "piece.h"

extern int Round_Count;         // from libsakk.c, not really sure where to put this.

enum { BOARD_ROW_SIZE = 10, BOARD_COL_SIZE = 10 };

extern PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

void draw_board();

void reset_board();

int convert_tile_letter_to_int(char ch);

int convert_tile_number_to_int(char ch);

bool move(Game *game, char *from, char *to);
void undo(Game* game);

bool load_from_file(char *input_name, int *global_round_count,
                    char *global_p1_name, char *global_p2_name, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]);
void save_to_file(char* file_name, int global_round_count, char* global_p1_name, char* global_p2_name);

bool can_castle_kingside();

bool can_castle_queenside();

#endif //C_CHESS_BOARD_H

//
// Created by gigi on 6/14/20.
//

#ifndef C_CHESS_BOARD_H
#define C_CHESS_BOARD_H

#include "game.h"
#include "piece.h"

extern int Round_Count;         // from libsakk.c, not really sure where to put this.
extern bool has_moved_white_king;              // D1
extern bool has_moved_white_rook_queenside;    // A1
extern bool has_moved_white_rook_kingside;     // H1

extern bool has_moved_black_king;              // D8
extern bool has_moved_black_rook_queenside;    // A8
extern bool has_moved_black_rook_kingside;     // H8


enum { BOARD_ROW_SIZE = 10, BOARD_COL_SIZE = 10 };

extern PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE];

void reset_has_moved_values();

void draw_board();

void reset_board();

bool move(Game *game, char *from, char *to);
void undo(Game* game);

bool load_from_file(char *input_name, int *global_round_count,
                    char *global_p1_name, char *global_p2_name, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]);
void save_to_file(char* file_name, int global_round_count, char* global_p1_name, char* global_p2_name);

bool can_castle_kingside();

bool can_castle_queenside();

void castle_queenside(Game* game);

void castle_kingside(Game* game);

bool castle(Game *game, char *from_king, char *from_rook, char *to_king, char *to_rook);

bool mutate_board(char *from, char *to);

#endif //C_CHESS_BOARD_H

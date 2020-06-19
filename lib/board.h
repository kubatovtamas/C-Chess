//
// Created by gigi on 6/14/20.
//

#ifndef C_CHESS_BOARD_H
#define C_CHESS_BOARD_H

#include "game.h"
#include "piece.h"

extern int Round_Count;
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

bool can_castle_kingside();

bool can_castle_queenside();

void castle_queenside(Game* game);

void castle_kingside(Game* game);

bool can_transform(int* pos, COLOR* color);

bool castle(Game *game, char *from_king, char *from_rook, char *to_king, char *to_rook);

bool mutate_board(char *from, char *to);

#endif //C_CHESS_BOARD_H

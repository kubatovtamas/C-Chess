//
// Created by gigi on 6/14/20.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "board.h"
#include "piece.h"

int round_count = 0;
//_Bool is_even(round_count) ? white : black
_Bool has_moved_white_king = 0;
_Bool has_moved_white_rook_long = 0;
_Bool has_moved_white_rook_short = 0;
_Bool has_moved_black_king = 0;
_Bool has_moved_black_rook_long = 0;
_Bool has_moved_black_rook_short = 0;

// Board tester
// Starting Position
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

void load_from_file(char* file_name, int* step, PIECE_TYPE game_board[8][8]) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
        return;
    fscanf(file_pointer, "%d ", &step);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fscanf(file_pointer, "%x ", &game_board[i][j]);
        }
    }
    fclose(file_pointer);
}

void save_to_file(char* file_name, int step, PIECE_TYPE game_board[8][8]) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "w");
    if (file_pointer == NULL)
        return;
    fprintf(file_pointer, "%d\n", step);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fprintf(file_pointer, "%x ", game_board[i][j]);
        }
        fprintf(file_pointer, "\n");
    }
    fclose(file_pointer);
}

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


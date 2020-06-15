//
// Created by gigi on 6/14/20.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "board.h"
#include "piece.h"
#include <stdbool.h>

int round_count = 0;
//_Bool is_even(round_count) ? white : black
bool has_moved_white_king = false;
bool has_moved_white_rook_long = false;
bool has_moved_white_rook_short = false;
bool has_moved_black_king = false;
bool has_moved_black_rook_long = false;
bool has_moved_black_rook_short = false;

// Board tester
// Starting Position
PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
        // Black
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'8', BLACKROOK, BLACKKNIGHT, BLACKBISHOP, BLACKQUEEN, BLACKKING, BLACKBISHOP, BLACKKNIGHT, BLACKROOK, '8'},
        {'7', BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, '7'},
        {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '6'},
        {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '5'},
        {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '4'},
        {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3'},
        {'2', WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, '2'},
        {'1', WHITEROOK, WHITEKNIGHT, WHITEBISHOP, WHITEQUEEN, WHITEKING, WHITEBISHOP, WHITEKNIGHT, WHITEROOK, '1'},
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}
        // White
};

void load_from_file(char* file_name, int* step, PIECE_T game_board[8][8]) {
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

void save_to_file(char* file_name, int step, PIECE_T game_board[8][8]) {
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
    setlocale(LC_CTYPE, "");
    for (int i = 0; i < BOARD_ROW_SIZE; i++) {
        for (int j = 0; j < BOARD_COL_SIZE; ++j) {
            wchar_t ch = Board[i][j];
            wprintf(L" %lc ", ch);
        }
        wprintf(L"\n");
    }
}

